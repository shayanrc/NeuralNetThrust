/*
 * Layer.cpp
 *
 *  Created on: 04-Dec-2013
 *      Author: xion
 */

#include "Layer.h"

template< typename T >
struct multiplyByConstant
{
    const T constant;

    multiplyByConstant(T _constant) : constant(_constant) {}

    __host__ __device__
        double operator()( T& VecElem) const {
            return VecElem*constant;
        }
};


Layer::Layer(int input_size, int output_size)
{
	init(input_size,output_size);

	learningRate=1;
	momentumConstant=0;
}


Layer::Layer(int input_size, int output_size,double _learningRate,double _momentumConstant)
{
	init(input_size,output_size);
	learningRate=_learningRate;
	momentumConstant=_momentumConstant;
}

void Layer::init(int input_size, int output_size)
{
	no_of_inputs=input_size+1;
	no_of_neurons=output_size;

	neurons=std::vector<Neuron>(no_of_neurons,Neuron(no_of_inputs));

	h_inputs=thrust::host_vector<double>(no_of_inputs);
	h_outputs=thrust::host_vector<double>(no_of_inputs,0);
	h_desired_outputs=thrust::host_vector<double>(no_of_neurons);
	h_dW=thrust::host_vector<double>(no_of_neurons);

	d_inputs=thrust::device_vector<double>(no_of_inputs);
	d_outputs=thrust::device_vector<double>(no_of_neurons);
	d_desired_outputs=thrust::device_vector<double>(no_of_neurons);
	d_dW=thrust::device_vector<double>(no_of_neurons);
	randomizeWeights();
}

void Layer::randomizeWeights()
{
	for(int neuronIndex=0; neuronIndex<neurons.size();neuronIndex++)
	{

		//std::cout<<"neuron :"<<neuronIndex<<" Randomize Weights\n";
		neurons[neuronIndex].randomizeWeights();
	}
}

//functor for sigmoid activation function
template< typename T >
struct activation
	{
		__host__ __device__ void operator()( T &x ) const {
		x = 1/(1+exp(-x));
	}
};

//functor for calculating derivative of sigmoid activation function
//template< typename T >
struct deactivation
	{
		__host__ __device__ void operator()( double &x ) const {
		x = x*(1-x);
	}
};

//Activation(Sum(Weight x Input))
void Layer::feedForward()
{

	//std::cout<<"Inside feedForward";
	thrust::device_vector<double> d_WxI=thrust::device_vector<double>(d_inputs.size());

	//std::cout<<"\nInputs : "<<d_inputs.size();
	//printVector(d_inputs);

	for(int neuronIndex=0;neuronIndex<no_of_neurons;neuronIndex++)
	{
		//d_inputs=h_inputs;

		//d_WxI=thrust::device_vector<double>(neurons[neuronIndex].d_weightVector.size());

		//std::cout<<"\nNeuron ["<<neuronIndex<<"] : feedforward :: "<<neurons[neuronIndex].d_weightVector.size()<<"\n";
		//printVector(neurons[neuronIndex].d_weightVector);




		//d_WxI = d_inputs * neurons[neuronIndex].d_weightVector;
		thrust::transform(d_inputs.begin(),d_inputs.end(),neurons[neuronIndex].d_weightVector.begin(),d_WxI.begin(),thrust::multiplies<double>());

//		std::cout<<"d_WxI :";
//		printVector(d_WxI);


		//d_outputs[neuronIndex] = sum(d_WxI)
		d_outputs[neuronIndex]=thrust::reduce(d_WxI.begin(),d_WxI.end());

		//std::cout<<"\nNeuron ["<<neuronIndex<<"] Output: "<<d_outputs[neuronIndex];


	}

	std::cout<<"\nfeedForward outputs before activation : ";
	printVector(d_outputs);
	//d_outputs=activation(d_outputs)
	thrust::for_each( d_outputs.begin() , d_outputs.end() , activation<double>() );
	std::cout<<"\nfeedForward outputs after activation : ";
	printVector(d_outputs);
}



void Layer::calculateError()
{
	std::cout<<"In calculate error\n";
	thrust::transform(d_desired_outputs.begin(),d_desired_outputs.end(),d_outputs.begin(),d_dW.begin(),thrust::minus<double>());

}


//Theres a bug here: if no of inputs and no of outputs are not same this fails TODO Fixit
void Layer::propagateBack(Layer *layer)
{
	thrust::device_vector<double> d_WxdW(no_of_inputs,0);
	thrust::fill(layer->d_dW.begin(),layer->d_dW.end(),0);
	for(unsigned int neuronIndex=0;neuronIndex<layer->d_dW.size();neuronIndex++)
	{
		//d_WxdW = d_dW * d_WxdW
		//thrust::transform(d_dW.begin(),d_dW.end(),neurons[neuronIndex].d_weightVector.begin(),d_WxdW.begin(),thrust::multiplies<double>());
		thrust::transform(neurons[neuronIndex].d_weightVector.begin(),neurons[neuronIndex].d_weightVector.end(),d_WxdW.begin(),multiplyByConstant<double>(d_dW[neuronIndex]));

		thrust::transform(d_WxdW.begin(),d_WxdW.end(),layer->d_dW.begin(),layer->d_dW.begin(),thrust::plus<double>());

		//prev_dW[i] = sum(d_WxdW)
		//layer.d_dW[neuronIndex]=thrust::reduce(d_WxdW.begin(),d_WxdW.end());
	}


	std::cout<<"\nd_dW in propagateBack: ";
	printVector(d_dW);
}

//Function to set the outputs as inputs of the next layer
//Recheck this function
void Layer::propagateOutput(Layer *layer)
{
	layer->d_inputs=d_outputs;

	//Add another input with value 1 for bias
	layer->d_inputs.push_back(1);

	std::cout<<"\npropagated Output: ";
	printVector(layer->d_inputs);
}

template< typename T >
struct modifyweight_functor
{
    const T learningRate;
    const T dW;

    modifyweight_functor(T _learningRate,T _dW) : learningRate(_learningRate),dW(_dW) {}

    __host__ __device__
        float operator()(const T& W, const T& I) const {
            return W+learningRate*dW*I;
        }
};

template< typename T >
struct calculateWeightChange
{
    const T learningRate;
    const T dW;

    calculateWeightChange(T _learningRate,T _dW) : learningRate(_learningRate),dW(_dW) {}

    __host__ __device__
        float operator()(const T& I) const {
            return learningRate*dW*I;
        }
};


template< typename T >
struct modifymomentum_functor
{
    //const T learningRate;
    const T momentumConstant;

    modifymomentum_functor(T _momentumConstant) : momentumConstant(_momentumConstant) {}

    __host__ __device__
        float operator()(const T& weightChange) const {
            return momentumConstant*weightChange;
        }
};

void Layer::modifyweights()
{

	thrust::device_vector<double> d_WeightChange=thrust::device_vector<double>(no_of_inputs);

	thrust::device_vector<double> d_deActivatedOutput=thrust::device_vector<double>(d_outputs);

	//thrust::device_vector<double> d_learningRate=thrust::device_vector<double>(no_of_inputs,learningRate);

	//Apply inverse activation function to the output
	thrust::for_each(d_deActivatedOutput.begin(),d_deActivatedOutput.end(),deactivation());

	std::cout<<"d_deActivatedOutput : ";
	printVector(d_deActivatedOutput);

	std::cout<<"d_dW : ";
	printVector(d_dW);

	//dW[neuronIndex]=deActivation(output[neuronIndex])*dW[neuronIndex];
	thrust::transform(d_deActivatedOutput.begin(),d_deActivatedOutput.end(),d_dW.begin(),d_dW.begin(),thrust::multiplies<double>());

	//std::cout<<"d_WeightChange : ";
	//printVector(d_WeightChange);

	//For each neuron:
	for(int neuronIndex=0;neuronIndex<no_of_neurons;neuronIndex++)
	{
		//TODO recheck the momentum logic I dont think it;s being done right
		//weightChange[neuronIndex][inputIndex]= LEARNING_RATE * dW[neuronIndex] * input[inputIndex];
		//weight[neuronIndex][inputIndex] = weight[neuronIndex][inputIndex]+weightChange[neuronIndex][inputIndex]

		/*std::cout<<"Neuron "<<neuronIndex<<" Weights before modifyweight: ";
		printVector(neurons[neuronIndex].d_weightVector);*/
		thrust::transform(d_inputs.begin(),d_inputs.end(),d_WeightChange.begin(),calculateWeightChange<double>(learningRate,d_dW[neuronIndex]));
		thrust::transform(d_WeightChange.begin(),d_WeightChange.end(),neurons[neuronIndex].d_weightVector.begin(),neurons[neuronIndex].d_weightVector.begin(),thrust::plus<double>());

		/*std::cout<<"Neuron "<<neuronIndex<<" Weights after modifyweight: ";
		printVector(neurons[neuronIndex].d_weightVector);*/

		//weight[neuronIndex][inputIndex] = weight[neuronIndex][inputIndex]+momentum[neuronIndex][inputIndex];
		thrust::transform(neurons[neuronIndex].d_momentum.begin(),neurons[neuronIndex].d_momentum.end(),neurons[neuronIndex].d_weightVector.begin(),neurons[neuronIndex].d_weightVector.begin(),thrust::plus<double>());


		//momentum[weightIndex]=MOMENTUM_CONSTANT*weightChange[weightIndex];
		thrust::transform(d_WeightChange.begin(),d_WeightChange.end(),neurons[neuronIndex].d_momentum.begin(),modifymomentum_functor<double>(momentumConstant));

	}

}

double Layer::getLearningRate() const {
	return learningRate;
}

void Layer::setLearningRate(double learningRate) {
	this->learningRate = learningRate;
}

double Layer::getMomentumConstant() const {
	return momentumConstant;
}

void Layer::setMomentumConstant(double momentumConstant) {
	this->momentumConstant = momentumConstant;
}

int Layer::getNoOfInputs() const {
	return no_of_inputs;
}

int Layer::getNoOfNeurons() const {
	return no_of_neurons;
}

/*thrust:: host_vector<double> Layer::getDesiredOutputs()
{
	return	h_desired_outputs;
}*/


std::vector<double> Layer::getDesiredOutputs(){

	std::vector<double> outputs(no_of_neurons);

	thrust::copy(h_desired_outputs.begin(),h_desired_outputs.end(),outputs.begin());
	return outputs;
}

std::vector<double> Layer::getinputs()
{
	std::vector<double> inputs(no_of_inputs);
	thrust::copy(h_inputs.begin(),h_inputs.end(),inputs.begin());
	return inputs;
}


/*thrust:: host_vector<double> Layer::getinputs()
{
	return h_inputs;
}*/


std::vector<double> Layer::getError()
{
	std::vector<double> error(no_of_neurons);
	h_dW=d_dW;
	thrust::copy(h_dW.begin(),h_dW.end(),error.begin());
	return error;
}

/*thrust:: host_vector<double> Layer::getError()
{
	h_dW=d_dW;
	return h_dW;
}*/

void Layer::setInputs(std::vector<double> inputs){

	h_inputs=inputs;

	//Add 1 to the end for bias
	h_inputs.push_back(1);

	//Copy to device
	d_inputs=h_inputs;

//	std::cout<<"Set inputs: ";
//	printVector(d_inputs);

}

void Layer::setInputs(thrust::host_vector<double> inputs){

	h_inputs=inputs;

	//Add 1 to the end for bias
	h_inputs.push_back(1);

	//Copy to device
	d_inputs=h_inputs;
}

void Layer::setDesiredOutputs(std::vector<double> outputs){


	h_desired_outputs=outputs;

	//Copy to device
	d_desired_outputs=h_desired_outputs;
}

/*thrust::host_vector<double> Layer::getOutputs(){

	h_outputs=d_outputs;
	return h_outputs;
}*/

std::vector<double> Layer::getOutputs(){
	//std::cout<<"Inside getOutputs";
	std::vector<double> outputs(no_of_neurons);
	h_outputs=d_outputs;
	//std::cout<<"Copied from device to host";
	thrust::copy(d_outputs.begin(),d_outputs.end(),outputs.begin());
	//std::cout<<"Copied from device to std";
	return outputs;
}

void Layer::identify()
{
	std::cout<<"Generic Layer!!";
}

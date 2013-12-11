/*
 * Layer.cpp
 *
 *  Created on: 04-Dec-2013
 *      Author: xion
 */

#include "Layer.h"

Layer::Layer(int input_size, int output_size)
{
	no_of_inputs=input_size;
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
template< typename T >
struct deactivation
	{
		__host__ __device__ void operator()( T &x ) const {
		x = x*(1-x);
	}
};

//Activation(Sum(Weight x Input))
void Layer::feedForward()
{
	thrust::device_vector<double> d_WxI;

	for(int neuronIndex=0;neuronIndex<no_of_neurons;neuronIndex++)
	{
		d_inputs=h_inputs;

		//d_WxI = neurons[neuronIndex].d_weightVector;
		d_WxI=thrust::device_vector<double>(neurons[neuronIndex].d_weightVector.begin(),neurons[neuronIndex].d_weightVector.end());

		//d_WxI = d_inputs * dWxI
		thrust::transform(d_inputs.begin(),d_inputs.end(),d_WxI.begin(),d_WxI.end(),thrust::multiplies<double>());

		//d_outputs[neuronIndex] = sum(d_WxI)
		d_outputs[neuronIndex]=thrust::reduce(d_WxI.begin(),d_WxI.end());
	}

	//d_outputs=activation(d_outputs)
	thrust::for_each( d_outputs.begin() , d_outputs.end() , activation<double>() );

}



void Layer::calculateError()
{
	thrust::transform(d_desired_outputs.begin(),d_desired_outputs.end(),d_outputs.begin(),d_dW.begin(),thrust::minus<double>());

}

void Layer::propagateBack(thrust::device_vector<double> prev_dW)
{
	thrust::device_vector<double> d_WxdW;

	for(int neuronIndex=0;neuronIndex<prev_dW.size();neuronIndex++)
		{
			//d_WxdW = neurons[i].d_weightVector;

			d_WxdW=thrust::device_vector<double>(neurons[neuronIndex].d_weightVector.begin(),neurons[neuronIndex].d_weightVector.end());

			//d_WxdW = d_inputs * d_WxdW
			thrust::transform(d_dW.begin(),d_dW.end(),d_WxdW.begin(),d_WxdW.end(),thrust::multiplies<double>());

			//prev_dW[i] = sum(d_WxdW)
			prev_dW[neuronIndex]=thrust::reduce(d_WxdW.begin(),d_WxdW.end());
		}

}

template< typename T >
struct modifyweight_functor
{
    const T learningRate;
    const T dW;

    modifyweight_functor(T _learningRate,T _dW) : learningRate(_learningRate),dW(_dW) {}

    __host__ __device__
        float operator()(const T& W, const T& I) const {
            return W-learningRate*dW*I;
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

	thrust::device_vector<double> d_learningRate=thrust::device_vector<double>(no_of_inputs,learningRate);

	thrust::for_each(d_deActivatedOutput.begin(),d_deActivatedOutput.end(),deactivation<double>());

	//dW[neuronIndex]=deActivation(output[neuronIndex])*dW[neuronIndex];
	thrust::transform(d_deActivatedOutput.begin(),d_deActivatedOutput.end(),d_dW.begin(),d_dW.end(),thrust::multiplies<double>());


	for(int neuronIndex=0;neuronIndex<no_of_neurons;neuronIndex++)
	{
		//weightChange[neuronIndex][inputIndex]= LEARNING_RATE * dW[neuronIndex] * input[inputIndex];
		//weight[neuronIndex][inputIndex] = weight[neuronIndex][inputIndex]+weightChange[neuronIndex][inputIndex]
		thrust::transform(d_WeightChange.begin(),d_WeightChange.end(),neurons[neuronIndex].d_weightVector.begin(),neurons[neuronIndex].d_weightVector.begin(),modifyweight_functor<double>(learningRate,d_dW[neuronIndex]));

		//weight[neuronIndex][inputIndex] = weight[neuronIndex][inputIndex]+momentum[neuronIndex][inputIndex];
		thrust::transform(neurons[neuronIndex].d_momentum.begin(),neurons[neuronIndex].d_momentum.end(),neurons[neuronIndex].d_weightVector.begin(),neurons[neuronIndex].d_weightVector.begin(),thrust::plus<double>());

		//momentum[weightIndex]=MOMENTUM_CONSTANT*weightChange[weightIndex];
		thrust::transform(d_inputs.begin(),d_inputs.end(),neurons[neuronIndex].d_momentum.begin(),modifymomentum_functor<double>(momentumConstant));
	}

}

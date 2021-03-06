// notch_filter.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#define Pi 3.1415926

// dlsim为一个可重载的函数，具体根据其参数数量来决定！最多有6个参数
void dlsim(MatrixXd *b, MatrixXd *a, MatrixXd *samples)
{

}

int main()
{
	// Read the wav file and convert it to matrix
	AudioFile<double> audioFile;
	string path = "C:\\Users\\11235\\Documents\\c++\\AudioFile\\tests\\AudioFileTests\\test-audio\\wav_stereo_24bit_48000.wav";
	int NLen = 1024;
	// Try to read the audio file
	try
	{
		audioFile.load(path);
		int channel = 0;
		int numSamples = audioFile.getNumSamplesPerChannel();
		if (numSamples < NLen)
			NLen = numSamples;

		// Input signal
		MatrixXd samples(NLen, 1);
		for (int i = 0; i < NLen; i++)
		{
			samples(i, 0) = audioFile.samples[channel][i];
		}
		cout << "Read done!" << endl;

		cout << "Begin to use fftw" << endl;

		int f0 = 50;
		double Ts = 0.001;
		double fs = 1 / Ts;

		double alpha = 2 * cos(2 * Pi * f0 *Ts);
		double beta = 0.96;
		MatrixXd b(3, 1);
		b(0, 0) = 1;
		b(1, 0) = alpha;
		b(2, 0) = 1;
		cout << "b:" << endl << b << endl;
		MatrixXd a(3, 1);
		a(0, 0) = 1;
		a(1, 0) = alpha * beta;
		a(2, 0) = beta * beta;
		cout << "a:" <<endl << a << endl;
		dlsim(&b, &a, &samples);

		fftw_complex *in, *out;
		fftw_plan p;

		int N = 100;
		in = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * N);
		out = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * N);
		p = fftw_plan_dft_1d(N, in, out, FFTW_FORWARD, FFTW_ESTIMATE);

		fftw_execute(p); /* repeat as needed */

		fftw_destroy_plan(p);
		fftw_free(in); fftw_free(out);
		system("pause");
	}
	// Unhandled error
	catch(int )
	{
		std::cout << "Audio File read fail!" << std::endl;
	}
    return 0;
}


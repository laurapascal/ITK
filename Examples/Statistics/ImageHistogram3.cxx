/*=========================================================================

  Program:   Insight Segmentation & Registration Toolkit
  Module:    ImageHistogram3.cxx
  Language:  C++
  Date:      $Date$
  Version:   $Revision$

  Copyright (c) Insight Software Consortium. All rights reserved.
  See ITKCopyright.txt or http://www.itk.org/HTML/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even 
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/

// Software Guide : BeginLatex
//
// This example shows how to compute the histogram of an RGB image.
// using the helper class \doxygen{ImageToHistogramGenerator}.
//
// In this first example we compute the histogram of each channel 
// independently.
//
// Software Guide : EndLatex 


// Software Guide : BeginCodeSnippet
#include "itkImageToHistogramGenerator.h"
#include "itkImage.h"
#include "itkRGBPixel.h"
// Software Guide : EndCodeSnippet

#include "itkImageFileReader.h"

int main( int argc, char * argv [] )
{

  if( argc < 2 )
    {
    std::cerr << "Missing command line arguments" << std::endl;
    std::cerr << "Usage :  ImageHistogram1  inputRGBImageFileName " << std::endl;
    return -1;
    }


  typedef unsigned char                         PixelComponentType;

  typedef itk::RGBPixel< PixelComponentType >   RGBPixelType;

  const unsigned int                            Dimension = 2;

  typedef itk::Image< RGBPixelType, Dimension > RGBImageType;

  typedef itk::ImageFileReader< RGBImageType >  ReaderType;

  ReaderType::Pointer reader = ReaderType::New();

  reader->SetFileName( argv[1] );

  try
    {
    reader->Update();
    }
  catch( itk::ExceptionObject & excp )
    {
    std::cerr << "Problem encoutered while reading image file : " << argv[1] << std::endl;
    std::cerr << excp << std::endl;
    return -1;
    }



  typedef itk::Statistics::ImageToHistogramGenerator< 
                                              RGBImageType 
                                                          >   HistogramGeneratorType;
  typedef HistogramGeneratorType::SizeType   SizeType;


  SizeType size;

  size[0] = 255;  // number of bins for the Red   channel
  size[1] =   1;  // number of bins for the Green channel
  size[2] =   1;  // number of bins for the Blue  channel


  HistogramGeneratorType::Pointer histogramGenerator = HistogramGeneratorType::New();

  histogramGenerator->SetInput(  reader->GetOutput()  );



  histogramGenerator->SetNumberOfBins( size );
  histogramGenerator->SetMarginalScale( 10.0 );
  histogramGenerator->Compute();

  typedef HistogramGeneratorType::HistogramType  HistogramType;

  const HistogramType * histogram = histogramGenerator->GetOutput();

  const unsigned int histogramSize = histogram->Size();

  std::cout << "Histogram size " << histogramSize << std::endl;

  unsigned int channel = 0;  // red channel

  std::cout << "Histogram of the red component" << std::endl;

  for( unsigned int bin=0; bin < histogramSize; bin++ )
    {
    std::cout << "bin = " << bin << " frequency = ";
    std::cout << histogram->GetFrequency( bin, channel ) << std::endl;
    }


  // Now compute the histogram for the Green component
  size[0] =   1;  // number of bins for the Red   channel
  size[1] = 255;  // number of bins for the Green channel
  size[2] =   1;  // number of bins for the Blue  channel

  histogramGenerator->SetNumberOfBins( size );
  histogramGenerator->SetMarginalScale( 10.0 );
  histogramGenerator->Compute();

  channel = 1;  // green channel

  std::cout << "Histogram of the green component" << std::endl;

  for( unsigned int bin=0; bin < histogramSize; bin++ )
    {
    std::cout << "bin = " << bin << " frequency = ";
    std::cout << histogram->GetFrequency( bin, channel ) << std::endl;
    }


  // Now compute the histogram for the Blue component
  size[0] =   1;  // number of bins for the Red   channel
  size[1] =   1;  // number of bins for the Green channel
  size[2] = 255;  // number of bins for the Blue  channel

  histogramGenerator->SetNumberOfBins( size );
  histogramGenerator->SetMarginalScale( 10.0 );
  histogramGenerator->Compute();

  channel = 2;  // blue channel

  std::cout << "Histogram of the blue component" << std::endl;

  for( unsigned int bin=0; bin < histogramSize; bin++ )
    {
    std::cout << "bin = " << bin << " frequency = ";
    std::cout << histogram->GetFrequency( bin, channel ) << std::endl;
    }


  // Now compute the joint histogram for the three components
  size[0] = 255;  // number of bins for the Red   channel
  size[1] = 255;  // number of bins for the Green channel
  size[2] = 255;  // number of bins for the Blue  channel

  histogramGenerator->SetNumberOfBins( size );
  histogramGenerator->SetMarginalScale( 10.0 );
  histogramGenerator->Compute();

  return 0;
  
}



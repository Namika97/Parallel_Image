import hipi.image.FloatImage;
import hipi.image.ImageHeader;
import hipi.imagebundle.mapreduce.ImageBundleInputFormat;

import java.io.IOException;

public class SampleProgram extends Configured implements Tool {


   public static class ProgramMapper extends Mapper<ImageHeader, FloatImage, IntWritable, FloatImage> {
       public void map(ImageHeader key, FloatImage value, Context context)
               throws IOException, InterruptedException {

                        
           if (value != null && value.getWidth() > 1 && value.getHeight() > 1 && value.getBands() == 3) //To check if the image is appropriate in terms of size and color channels : R, G, B
           {

               int wid = value.getWidth(); //Get the width of the image
               int hgt = value.getHeight(); //Get the height of image
               
               float[] imgData = value.getData(); //Image Data

               float[] rgbData = {0,0,0}; // Array created to store RGB values
            
               for (int j = 0; j < h; j++) {
                   for (int i = 0; i < w; i++) {
                       rgbData[0] += imgData[(j*w+i)*3+0]; // R
                       rgbData[1] += imgData[(j*w+i)*3+1]; // G
                       rgbData[2] += imgData[(j*w+i)*3+2]; // B
                   }
               }

               FloatImage avg = new FloatImage(1, 1, 3, rgbData); 

               avg.scale(1.0f/(float)(w*h)); //The floated image is scaled

               context.write(new IntWritable(1), avg);


           } 


       } 
   }





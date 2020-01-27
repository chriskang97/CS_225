#include "Image.h" 

#include "cs225/PNG.h" 
using cs225::PNG ; 

#include "cs225/HSLAPixel.h" 
using cs225::HSLAPixel ;

#include <iostream> 
#include <cmath>
using namespace std ; 

void Image::lighten() 
{
	for (unsigned x = 0 ; x < width() ; x++ ) 
	{
		for (unsigned y = 0 ; y < height() ; y++ )
		{
			// Checking whether boundaries [0,1] are past. 
			if ( getPixel(x,y).l + 0.1 > 1.0 ) 
			{
				getPixel(x,y).l = 1.0 ; 
			}
			
			else if ( getPixel(x,y).l + 0.1 < 0 ) 
			{
				getPixel(x,y).l = 0.0 ; 
			}
			
			else 			
			{
				getPixel(x,y).l = getPixel(x,y).l + 0.1 ;
			} 
		}
	}
}

void Image::lighten(double amount) 
{
	for (unsigned x = 0 ; x < width() ; x++ ) 
	{
		for (unsigned y = 0 ; y < height() ; y++ )
		{
			// Checking whether boundaries [0,1] are past. 			
			if ( getPixel(x,y).l + amount > 1.0 ) 
			{
				getPixel(x,y).l = 1.0 ; 
			}
			
			else if ( getPixel(x,y).l + amount < 0 ) 
			{
				getPixel(x,y).l = 0.0 ; 
			}
			
			else 
			{
				getPixel(x,y).l = getPixel(x,y).l + amount ; 
			}
		}
	}	
}

void Image::darken() 
{
	for (unsigned x = 0 ; x < width() ; x++ ) 
	{
		for (unsigned y = 0 ; y < height() ; y++ )
		{
			// Checking whether boundaries [0,1] are past. 			
			if ( getPixel(x,y).l - 0.1 > 1.0 ) 
			{
				getPixel(x,y).l = 1.0 ; 
			}
			
			else if ( getPixel(x,y).l - 0.1 < 0 ) 
			{
				getPixel(x,y).l = 0.0 ; 
			}
			
			else 
			{
				getPixel(x,y).l = getPixel(x,y).l - 0.1 ; 
			}
		}
	}	
}
 
void Image::darken(double amount) 
{
	for (unsigned x = 0 ; x < width() ; x++ ) 
	{
		for (unsigned y = 0 ; y < height() ; y++ )
		{
			// Checking whether boundaries [0,1] are past. 			
			if ( getPixel(x,y).l - amount > 1.0 ) 
			{
				getPixel(x,y).l = 1.0 ; 
			}
			
			else if ( getPixel(x,y).l - amount < 0 ) 
			{
				getPixel(x,y).l = 0.0 ; 
			}
			
			else 
			{
				getPixel(x,y).l = getPixel(x,y).l - amount ; 
			}
		}
	}		
}

void Image::saturate() 
{
	for (unsigned x = 0 ; x < width() ; x++ ) 
	{
		for (unsigned y = 0 ; y < height() ; y++ )
		{
			// Checking whether boundaries [0,1] are past. 			
			if ( getPixel(x,y).s + 0.1 > 1.0 ) 
			{
				getPixel(x,y).s = 1.0 ; 
			}
			
			else if ( getPixel(x,y).s + 0.1 < 0 ) 
			{
				getPixel(x,y).s = 0.0 ; 
			}
			
			else 
			{
				getPixel(x,y).s = getPixel(x,y).s + 0.1 ; 
			}
		}
	}		
}

void Image::saturate(double amount) 
{
	for (unsigned x = 0 ; x < width() ; x++ ) 
	{
		for (unsigned y = 0 ; y < height() ; y++ )
		{
			// Checking whether boundaries [0,1] are past. 			
			if ( getPixel(x,y).s + amount > 1.0 ) 
			{
				getPixel(x,y).s = 1.0 ; 
			}
			
			else if ( getPixel(x,y).s + amount < 0 ) 
			{
				getPixel(x,y).s = 0.0 ; 
			}
			
			else 
			{
				getPixel(x,y).s = getPixel(x,y).s + amount ; 
			}
		}
	}	
}

void Image::desaturate() 
{
	for (unsigned x = 0 ; x < width() ; x++ ) 
	{
		for (unsigned y = 0 ; y < height() ; y++ )
		{
			// Checking whether boundaries [0,1] are past. 			
			if ( getPixel(x,y).s - 0.1 > 1.0 ) 
			{
				getPixel(x,y).s = 1.0 ; 
			}
			
			else if ( getPixel(x,y).s - 0.1 < 0 ) 
			{
				getPixel(x,y).s = 0.0 ; 
			}
			
			else 
			{
				getPixel(x,y).s = getPixel(x,y).s - 0.1 ; 
			}
		}
	}	
}

void Image::desaturate(double amount) 
{
	for (unsigned x = 0 ; x < width() ; x++ ) 
	{
		for (unsigned y = 0 ; y < height() ; y++ )
		{
			// Checking whether boundaries [0,1] are past. 			
			if ( getPixel(x,y).s - amount > 1.0 ) 
			{
				getPixel(x,y).l = 1.0 ; 
			}
			
			else if ( getPixel(x,y).s - amount < 0 ) 
			{
				getPixel(x,y).l = 0.0 ; 
			}
			
			else 
			{
				getPixel(x,y).s = getPixel(x,y).s - amount ; 
			}
		}
	}	
}

void Image::grayscale() 
{
	for (unsigned x = 0 ; x < width() ; x++ ) 
	{
		for (unsigned y = 0 ; y < height() ; y++ )
		{
			getPixel(x,y).s = 0 ; 
		}
	}		
}

void Image::rotateColor(double degrees)
{
	for (unsigned x = 0 ; x < width() ; x++ ) 
	{
		for (unsigned y = 0 ; y < height() ; y++ )
		{
			// Checking whether boundaries [0,360] are past. 			
			if ( getPixel(x,y).h + degrees > 360 ) 
			{
				getPixel(x,y).h = (getPixel(x,y).h + degrees ) - 360 ; 
			}
			
			else if ( getPixel(x,y).h + degrees < 0 ) 
			{
				getPixel(x,y).h = 360 + ( getPixel(x,y).h + degrees ) ; 
			}
			
			else 
			{
				getPixel(x,y).h = getPixel(x,y).h + degrees ; 
			} 
		}
	}	
}
 
void Image::illinify() 
{
	for ( unsigned x = 0; x < width(); x++ )
	{
		for ( unsigned y = 0; y < height(); y++ )
		{
			// Obtain Current Hue Value
			double Current_Hue_Value = getPixel(x,y).h ;

			// Need to check the distance both counterclockwise and clockwise
			double orange_distance_1 = abs( Current_Hue_Value - 11 ) ;
			double orange_distance_2 = abs( 360 - Current_Hue_Value + 11 ) ;
			double blue_distance_1 = abs( Current_Hue_Value - 216 ) ;
			double blue_distance_2 = abs( 360 - Current_Hue_Value + 216 ) ;

			double least_orange_distance = 0 ;
			double least_blue_distance = 0 ;

			// Determine which of the distance is shortest
			if ( orange_distance_1 < orange_distance_2 )
			{
				least_orange_distance = orange_distance_1 ;
			}

			else

			{
				least_orange_distance = orange_distance_2 ;
			}

			if ( blue_distance_1 < blue_distance_2 )
			{
				least_blue_distance = blue_distance_1 ;
			}

			else

			{
				least_blue_distance = blue_distance_2 ;
			}

			// Determine which color to use. Whichever has least distance toward each color will be chosen.
			if ( least_orange_distance  < least_blue_distance  )
			{
				getPixel(x,y).h = 11 ;
			}

			else
			{
				getPixel(x,y).h = 216 ;
			}

		}
	}
}

void Image::scale(double factor) 
{
	PNG reference = *this ; 
	resize( factor * width(), factor * height() ) ;  
	
	unsigned ref_x = 0 ;
	unsigned ref_y = 0 ; 

	double x_double = 0 ; 
	double y_double = 0 ; 

	int x_mod_result = 0 ; 
	int y_mod_result = 0 ;	
	
	for ( unsigned x = 0; x < width(); x++ )
	{
		if ( x == 0 ) 
		{
			
		}
		
		// Condition for Scaling greater than 1 
		else if (factor >= 1.0 ) 
		{
			x_double = x ; 
			x_mod_result = fmod( x_double, factor) ; 	
					
			if ( x_mod_result == 0 ) 
			{
				ref_x = ref_x + 1 ; 
			}
		}
		
		else 
		
		// Condition for Scaling Less Than 1 
		{
			ref_x = ref_x + (unsigned)( 1/factor ); 
		}
		
		ref_y = 0 ; 
		
		for ( unsigned y = 0; y < height(); y++ )
		{	
			if ( y == 0 ) 
			{
				
			}

			// Condition for Scaling Greater Than 1 			
			else if (factor >= 1.0 ) 
			{
				y_double = y ; 
				y_mod_result = fmod( y_double, factor) ;
				 				
				if ( y_mod_result == 0  ) 
				{
					ref_y = ref_y + 1 ; 	
				}
			}
			
			// Condition for Scaling Less Than 1 			
			else 
			{
				ref_y = ref_y + (unsigned)( 1/factor ) ; 
			}			
			
			getPixel(x,y).h = reference.getPixel(ref_x,ref_y).h ; 
			getPixel(x,y).s = reference.getPixel(ref_x,ref_y).s ; 
			getPixel(x,y).l = reference.getPixel(ref_x,ref_y).l ; 
			getPixel(x,y).a = reference.getPixel(ref_x,ref_y).a ; 				
				
		}	
	}
		
}

void Image::scale(unsigned w, unsigned h) 
{
	PNG reference = *this ; 
	
	unsigned ref_x = 0 ;
	unsigned ref_y = 0 ; 
	
	double scale_x = (double)w / width() ; 
	double scale_y = (double)h / height() ; 

	double x_double = 0 ; 
	double y_double = 0 ; 
	
	int x_mod_result = 0 ; 
	int y_mod_result = 0 ; 
	
	resize( w, h ) ;  	
	
	for ( unsigned x = 0; x < width(); x++ )
	{
		x_double = x ; 
		x_mod_result = fmod( x_double, scale_x) ; 		
		
		if ( x == 0 ) 
		{
			
		}
		
		// Condition for Scaling greater than 1 
		else if (scale_x >= 1.0 ) 
		{
			if ( x_mod_result == 0 ) 
			{
				ref_x = ref_x + 1 ; 
			}
		}
		
		else 
		
		// Condition for Scaling Less Than 1 
		{
			ref_x = ref_x + (unsigned)( 1/scale_x);
		}
		
		ref_y = 0 ; 
		
		for ( unsigned y = 0; y < height(); y++ )
		{	
			y_double = y ; 
			y_mod_result = fmod( y_double, scale_y) ; 
			
			if ( y == 0 ) 
			{
				
			}
			
			// Condition for Scaling Greater Than 1 		
			else if (scale_y >= 1.0 ) 
			{
				if ( y_mod_result == 0  ) 
				{
					ref_y = ref_y + 1 ; 
				}
			}
			
			// Condition for Scaling Less Than 1 		
			else 
			{
				ref_y = ref_y + (unsigned)( 1/scale_y ) ; 
			}			
			
			getPixel(x,y).h = reference.getPixel(ref_x,ref_y).h ; 
			getPixel(x,y).s = reference.getPixel(ref_x,ref_y).s ; 
			getPixel(x,y).l = reference.getPixel(ref_x,ref_y).l ; 
			getPixel(x,y).a = reference.getPixel(ref_x,ref_y).a ; 				
				
		}	
	}
}

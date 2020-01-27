/**
 * @file StickerSheet.h
 * Contains your declaration of the interface for the StickerSheet class.
 */
#pragma once

#ifndef STICKERSHEET_H  
#define STICKERSHEET_H 

#include "Image.h" 

class Sticker
{
	public : 
		Sticker() 
		{
			sticker_pic = NULL ; 
			sticker_x = 0 ; 
			sticker_y = 0 ; 		
		}
			
		Sticker(Image* Sticker_, unsigned x, unsigned y )  
		{
			sticker_pic = Sticker_ ; 
			sticker_x = x ; 
			sticker_y = y ; 
		} 

		Image* sticker_pic ; 
		unsigned sticker_x ; 
		unsigned sticker_y ; 
}; 

class StickerSheet 
{
	
	public : 
		StickerSheet( const Image &picture, unsigned max) ;
		~StickerSheet() ; 
		StickerSheet(const StickerSheet &other) ;
		StickerSheet & operator=( const StickerSheet &other ) ; 
		void changeMaxStickers(unsigned max) ; 
		int addSticker(Image &sticker, unsigned x, unsigned y) ; 
		bool  translate( unsigned index, unsigned x, unsigned y) ; 
		void removeSticker(unsigned index) ; 
		Image* getSticker(unsigned index) const ; 
		Image render() const ; 
		
		//Helper Functions 
		void deep_copy( Sticker* output, Sticker* input, unsigned max ) ; 
		unsigned check_range( unsigned value, unsigned max_value ) ;
		
	private : 
		Image* base_pic ; 
		Image* sticker_pic_comb ; 
		unsigned max_stickers ; 
		unsigned num_stickers ; 
				
		Sticker* sticker_sheet ;   		

}; 



#endif 

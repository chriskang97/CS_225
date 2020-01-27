#include "StickerSheet.h"
#include "Image.h"

StickerSheet:: StickerSheet( const Image &picture, unsigned max)
{
	sticker_sheet = new Sticker [max] ;

	base_pic = new Image  ;
	*base_pic = picture ;

	sticker_pic_comb = new Image ;
	*sticker_pic_comb = picture ;

	max_stickers = max ;
	num_stickers = 0 ;

	for ( unsigned i = 0 ; i <  max_stickers ; i++ )
	{
		sticker_sheet[i].sticker_pic = NULL ;
	}

}

StickerSheet::~StickerSheet()
{
	if (sticker_sheet != NULL )
	{
		delete [] sticker_sheet ;
	}

	delete sticker_pic_comb ;
	delete base_pic ;

}

StickerSheet::StickerSheet(const StickerSheet &other)
{
	this->sticker_sheet = new Sticker [other.max_stickers] ;
	for ( unsigned i = 0 ; i <  other.max_stickers ; i++ )
	{
		sticker_sheet[i].sticker_pic = NULL ;
	}

	this->base_pic = new Image ;
	*(this->base_pic) = *(other.base_pic) ;
	this->sticker_pic_comb = new Image ;
	*(this->sticker_pic_comb) = *(other.sticker_pic_comb) ;

	this->max_stickers = other.max_stickers ;
	this->num_stickers = other.num_stickers ;

	deep_copy( this->sticker_sheet, other.sticker_sheet, this->max_stickers) ;
}

StickerSheet & StickerSheet::operator=( const StickerSheet &other )
{
	StickerSheet::~StickerSheet () ;

	this->sticker_sheet = new Sticker [other.max_stickers] ;
	for ( unsigned i = 0 ; i <  other.max_stickers ; i++ )
	{
		sticker_sheet[i].sticker_pic = NULL ;
	}

	this->base_pic = new Image ;
	*(this->base_pic) = *(other.base_pic) ;
	this->sticker_pic_comb = new Image ;
	*(this->sticker_pic_comb) = *(other.sticker_pic_comb) ;

	max_stickers = other.max_stickers ;
	num_stickers = other.num_stickers ;

	deep_copy( this->sticker_sheet, other.sticker_sheet, this->max_stickers) ;

	return *this ;
}

void StickerSheet::changeMaxStickers(unsigned max)
{
	unsigned max_test = 0 ;

	if ( this->max_stickers > max )
	{
		max_test = this->max_stickers ;
	}

	else
	{
		max_test = max ;
	}

	Sticker* temp_sticker_sheet = new Sticker[max_test ] ;

	for ( unsigned i = 0 ; i <  max_stickers ; i++ )
	{
		temp_sticker_sheet[i].sticker_pic = NULL ;
	}

	deep_copy( temp_sticker_sheet, this->sticker_sheet, this->max_stickers) ;

	delete [] this->sticker_sheet ;
	this->sticker_sheet = new Sticker[max] ;

	for ( unsigned i = 0 ; i <  max ; i++ )
	{
		this->sticker_sheet[i].sticker_pic = NULL ;
	}

	if ( this->num_stickers > max )
	{
		this->num_stickers = max ;
	}

	this->max_stickers = max ;

	deep_copy( this->sticker_sheet, temp_sticker_sheet, this->max_stickers) ;
	delete [] temp_sticker_sheet ;

}

int StickerSheet::addSticker(Image &sticker, unsigned x, unsigned y)
{
	if ( num_stickers >= max_stickers  )
	{
		return -1 ;
	}

	else

	{
		for( unsigned i = 0 ; i < max_stickers ; i ++ )
		{
			if( sticker_sheet[i].sticker_pic == NULL )
			{
				sticker_sheet[i] = Sticker( &sticker, x, y) ;
				num_stickers = num_stickers + 1 ;

				return i ;
			}
		}

	}

	return 0 ;
}

bool StickerSheet::translate( unsigned new_index, unsigned x, unsigned y)
{
	if ( new_index > max_stickers  )
	{
		return false ;
	}

	else if ( sticker_sheet[new_index].sticker_pic == NULL )
	{
		return false ;
	}

	else
	{
		sticker_sheet[new_index].sticker_x = x ;
		sticker_sheet[new_index].sticker_y = y ;

		return true ;
	}
}

void StickerSheet::removeSticker(unsigned index)
{
	// Potential Leak

	if ( index < max_stickers )
	{
		sticker_sheet[index].sticker_pic = NULL ;
		sticker_sheet[index].sticker_x = 0 ;
		sticker_sheet[index].sticker_y = 0 ;
	}
}

Image* StickerSheet::getSticker(unsigned index) const
{
	if ( index < max_stickers )
	{
		return sticker_sheet[index].sticker_pic ;
	}

	else
	{
		return NULL ;
	}

	return NULL ;
}

Image StickerSheet::render() const
{

	for ( unsigned sticker_num = 0 ; sticker_num < max_stickers ; sticker_num++)
	{
		if(sticker_sheet[sticker_num].sticker_pic != NULL )
		{
			unsigned base_x = sticker_sheet[sticker_num].sticker_x ;
			unsigned base_y = sticker_sheet[sticker_num].sticker_y ;

			for ( unsigned x = 0; x < sticker_sheet[sticker_num].sticker_pic->width() ; x++ )
			{
				for ( unsigned y = 0 ; y < sticker_sheet[sticker_num].sticker_pic->height() ; y++ )
				{
					if (sticker_sheet[sticker_num].sticker_pic->getPixel(x,y).a != 0 )
					{
						if (base_x + x > sticker_pic_comb->width() - 1 )
						{
							sticker_pic_comb->resize(sticker_pic_comb->width() + sticker_sheet[sticker_num].sticker_pic->width() - x + 1,  sticker_pic_comb->height() ) ;
						}

						if( base_y + y > sticker_pic_comb->height() - 1 )
						{
							sticker_pic_comb->resize(sticker_pic_comb->width(), sticker_pic_comb->height() + sticker_sheet[sticker_num].sticker_pic->height() - y + 1) ;
						}

						sticker_pic_comb->getPixel(base_x+x, base_y+y).h = sticker_sheet[sticker_num].sticker_pic->getPixel(x, y).h ;
						sticker_pic_comb->getPixel(base_x+x, base_y+y).s = sticker_sheet[sticker_num].sticker_pic->getPixel(x, y).s ;
						sticker_pic_comb->getPixel(base_x+x, base_y+y).a = sticker_sheet[sticker_num].sticker_pic->getPixel(x, y).a ;
						sticker_pic_comb->getPixel(base_x+x, base_y+y).l = sticker_sheet[sticker_num].sticker_pic->getPixel(x, y).l ;
					}
				}
			}
		}
	}

	return *sticker_pic_comb ;

}


// HELPER FUNCTIONS
unsigned StickerSheet::check_range( unsigned value, unsigned max_value )
{
	if (value >= max_value )
	{
		return max_value - 1 ;
	}

	return value ;
}

//POTENTIAL ERROR
void StickerSheet::deep_copy( Sticker* output, Sticker* input, unsigned max )
{
	for (unsigned i = 0 ; i < max ; i++ )
	{
		if(input[i].sticker_pic != NULL )
		{
			output[i].sticker_pic = input[i].sticker_pic ;
			output[i].sticker_x = input[i].sticker_x ;
			output[i].sticker_y = input[i].sticker_y ;
		}

	}

}

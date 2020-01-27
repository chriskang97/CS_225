/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>
#include "maptiles.h"
//#include "cs225/RGB_HSL.h"

using namespace std;


Point<3> convertToXYZ(LUVAPixel pixel) {
    return Point<3>( pixel.l, pixel.u, pixel.v );
}

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage>& theTiles)
{
    /**
     * @todo Implement this function!
     */

    MosaicCanvas* output_mosaic = new MosaicCanvas( theSource.getRows(), theSource.getColumns() ) ;

    // OBTAINING AVERAGE COLOR FOR EACH TILE IMAGE
    for ( int i = 0 ; i < theSource.getRows() ; i++ )
      for ( int j = 0 ; j < theSource.getColumns() ; j++ )
      {
        vector<Point<3>> list_region ;
        map< Point<3>, int > avgcolor_to_tile ;

        for ( unsigned long tile_image = 0 ; tile_image < theTiles.size() ; tile_image++ )
        {
          LUVAPixel region_color = theTiles[tile_image].getAverageColor() ;

          list_region.push_back( convertToXYZ( region_color) );
          avgcolor_to_tile.insert(pair <Point<3>, int> (convertToXYZ(region_color), tile_image) ) ;
        }

        KDTree<3> region_tree ( list_region ) ;
        Point<3> near = region_tree.findNearestNeighbor( convertToXYZ(theSource.getRegionColor(i, j)  ) ) ;

        auto find_tile = avgcolor_to_tile.find(near) ;
        output_mosaic->setTile( i, j, &theTiles.at( find_tile->second ) ) ;


      }




    return output_mosaic ;
}

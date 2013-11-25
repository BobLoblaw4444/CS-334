// SimplexNoise1234
// Copyright © 2003-2011, Stefan Gustavson
//
// Contact: stegu@itn.liu.se
//
// This library is public domain software, released by the author
// into the public domain in February 2011. You may do anything
// you like with it. You may even remove all attributions,
// but of course I'd appreciate it if you kept my name somewhere.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.
//
// Found here: http://staffwww.itn.liu.se/~stegu/aqsis/aqsis-newnoise/
//
// I removed all of the code to compute 1D, 3D, and 4D noise, since 
// I don't need any of it for my project.

class SimplexNoise {

  public:
    SimplexNoise() {}
    ~SimplexNoise() {}

/** 2D float Simplex noise
 */
    static float SimplexNoise::noise( float x, float y );

  private:
    static unsigned char SimplexNoise::perm[];
    static float  SimplexNoise::grad( int hash, float x, float y );
};


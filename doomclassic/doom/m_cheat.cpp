/*
===========================================================================

Doom 3 BFG Edition GPL Source Code
Copyright (C) 1993-2012 id Software LLC, a ZeniMax Media company. 

This file is part of the Doom 3 BFG Edition GPL Source Code ("Doom 3 BFG Edition Source Code").  

Doom 3 BFG Edition Source Code is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Doom 3 BFG Edition Source Code is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Doom 3 BFG Edition Source Code.  If not, see <http://www.gnu.org/licenses/>.

In addition, the Doom 3 BFG Edition Source Code is also subject to certain additional terms. You should have received a copy of these additional terms immediately following the terms and conditions of the GNU General Public License which accompanied the Doom 3 BFG Edition Source Code.  If not, please request a copy in writing from id Software at the address below.

If you have questions concerning this license or the applicable additional terms, you may contact in writing id Software LLC, c/o ZeniMax Media Inc., Suite 120, Rockville, Maryland 20850 USA.

===========================================================================
*/

#include "Precompiled.h"
#include "globaldata.h"

#include "m_cheat.h"

//
// CHEAT SEQUENCE PACKAGE
//



//
// Called in st_stuff module, which handles the input.
// Returns a 1 if the cheat was successful, 0 if failed.
//
//GK improved method
int
cht_CheckCheat
(const unsigned char*	cht,
	unsigned char*		key,
	int					ind,
	int&			   vote,
	bool buffer)
{
	if (!::g->classiccheats) {
		return 0;
	}
	int i = 0;
	int rc = 0;
	int score = 0; //GK: This score count the similarity of the current input with the cheat code
	while (cht[i] != 0xff) {
		if (cht[i] == key[i]) {
			rc = 1;
			score++;
		}
		else {
			rc = 0;
			break;
		}
		i++;
	}
	if (rc) {

		if (buffer) {
			if (ind >= i + 2) {
				for (int j = 0; j < 3; j++) {
					buf[j] = key[i + j];
				}
			}
			else if (ind >= i + 1) {
				if (score == ind-1) { //GK: Only one number missing vote it up
					vote++;
				}
				return 0;
			}
			else {
				if (score == ind) { //GK: Only some numbers missing vote it up
					vote ++;
				}
				return 0;
			}
		}
	}
	else {
		if (score == ind) { //GK: Close enough vote it up
			vote++;
		}
	}
	return rc;
}
//GK end
/*int
cht_CheckCheatN
( cheatseq_t*	cht,
char		key)
{
return 0; // ALAN : Checking the cheats CRASHES??
int i;
int rc = 0;
idLib::Printf("%i\n", key);
if (::g->firsttime)
{
::g->firsttime = 0;
for (i=0;i<256;i++) ::g->cheat_xlate_table[i] = SCRAMBLE(i);

}

if (!cht->p && cht->sequence)
{

cht->p = ::g->cheatbuffer + ::g->usedcheatbuffer;

int isize = 0;
while (cht->sequence[isize] != 0xff) { //root of evil

cht->p[isize] = cht->sequence[isize];
isize++;
}
idLib::Printf("HI\n");
cht->p[isize] = 0xff;
::g->usedcheatbuffer += isize;
::g->usedcheatbuffer ++;
}


if (*cht->p == 0)
*(cht->p++) = key;
else if
(::g->cheat_xlate_table[(unsigned char)key] == *cht->p) cht->p++;
else
{
int isize = 0;
while (cht->sequence[isize] != 0xff) {
cht->p[isize] = cht->sequence[isize];
isize++;
}
cht->p[isize] = 0xff;
}

if (*cht->p == 1)
cht->p++;
else if (*cht->p == 0xff) // end of sequence character
{
int isize = 0;
while (cht->sequence[isize] != 0xff) {
cht->p[isize] = cht->sequence[isize];
isize++;
}
cht->p[isize] = 0xff;
rc = 1;
}

return rc;
}*/

/*void
cht_GetParam
( cheatseq_t*	cht,
char*		buffer )
{


unsigned char pb[16];
unsigned char *p;
unsigned char c;

int isize = 0;

while(cht->sequence[isize] != 0xff) pb[isize] = cht->sequence[isize];
pb[isize] = 0xff;
p = &pb[0];

while (*(p++) != 1);

do
{
c = *p;
*(buffer++) = c;
*(p++) = 0;
}
while (c && *p!=0xff );

if (*p==0xff)
*buffer = 0;


}*/




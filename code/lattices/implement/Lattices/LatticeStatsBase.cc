//# LatticeStatsBase.cc: base class for LatticeStatistics.cc
//# Copyright (C) 1996,1999
//# Associated Universities, Inc. Washington DC, USA.
//#
//# This library is free software; you can redistribute it and/or modify it
//# under the terms of the GNU Library General Public License as published by
//# the Free Software Foundation; either version 2 of the License, or (at your
//# option) any later version.
//#
//# This library is distributed in the hope that it will be useful, but WITHOUT
//# ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
//# FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Library General Public
//# License for more details.
//#
//# You should have received a copy of the GNU Library General Public License
//# along with this library; if not, write to the Free Software Foundation,
//# Inc., 675 Massachusetts Ave, Cambridge, MA 02139, USA.
//#
//# Correspondence concerning AIPS++ should be addressed as follows:
//#        Internet email: aips2-request@nrao.edu.
//#        Postal address: AIPS++ Project Office
//#                        National Radio Astronomy Observatory
//#                        520 Edgemont Road
//#                        Charlottesville, VA 22903-2475 USA
//#
//# $Id$

#include <trial/Lattices/LatticeStatsBase.h>

#include <aips/Arrays/Vector.h>
#include <aips/Arrays/ArrayUtil.h>
#include <aips/Lattices/IPosition.h>
#include <aips/Mathematics/Math.h>
#include <aips/Utilities/String.h>
#include <aips/Utilities/Regex.h>

#include <iostream.h>


Vector<Int> LatticeStatsBase::toStatisticTypes (const String& statsU, 
                                                const Regex& delimiter)
{ 
   Vector<String> statsStrings = stringToVector(statsU, delimiter);
   return LatticeStatsBase::toStatisticTypes(statsStrings);
}

Vector<Int> LatticeStatsBase::toStatisticTypes (const Vector<String>& statsU)
{ 
   const uInt n = statsU.nelements();
   Vector<Int> statsToPlot(n);
   Int n2 = 0;
   for (uInt i=0; i<n; i++) {
      Int tmp = LatticeStatsBase::toStatisticType(statsU(i));
      if (tmp!=-1) {
         statsToPlot(n2) = tmp;
         n2++;
      }
   }
   statsToPlot.resize(n2, True);
   return statsToPlot;
}

Int LatticeStatsBase::toStatisticType (const String& statU)
{ 
   String stat = statU;
   stat.upcase();
   Int statToPlot = -1;
   if (stat.contains("NPTS")) {
      statToPlot = NPTS;
   } else if (stat.contains("SUMSQ")) {
      statToPlot = SUMSQ;
   } else if (stat.contains("SUM")) {  
      statToPlot = SUM;
   } else if (stat.contains("MEAN")) {
      statToPlot = MEAN;
   } else if (stat.contains("VAR")) {
      statToPlot = VARIANCE;
   } else if (stat.contains("SIG")) {
      statToPlot = SIGMA;
   } else if (stat.contains("RMS")) {
      statToPlot = RMS;
   } else if (stat.contains("MIN")) {
      statToPlot = MIN;
   } else if (stat.contains("MAX")) {
      statToPlot = MAX;
   } else if (stat.contains("FLUX")) {
      statToPlot = FLUX;
   }
   return statToPlot;
}  

Bool LatticeStatsBase::setNxy (Vector<Int>& nxy,
                               ostream& os)
{
   Int n = nxy.nelements();
   nxy.resize(2,True);
   if (n > 2) {
      os << "Too many elements for argument nxy" << endl;
      return False;
   } else if (n == 2) {
      nxy(0) = max(1,nxy(0));
      nxy(1) = max(1,nxy(1));
   } else if (n == 1) {
      nxy(0) = max(1,nxy(0));
      nxy(1) = nxy(0);
   } else {
      nxy(0) = 1;
      nxy(1) = 1;
   }
   return True;
}

void LatticeStatsBase::setStorageImageShape(IPosition& storeImageShape,
                                            const Bool& last,
                                            const Int& axisSize,
                                            const Vector<Int>& displayAxes, 
                                            const IPosition& imageShape)
{
   Int nStoreImageDim = displayAxes.nelements() + 1;
   storeImageShape.resize(nStoreImageDim);

   if (last) {
      for (Int i=0; i<nStoreImageDim-1; i++) storeImageShape(i) = imageShape(displayAxes(i));
      storeImageShape(nStoreImageDim-1) = axisSize;
   } else {
      for (Int i=1; i<nStoreImageDim; i++) 
        storeImageShape(i) = imageShape(displayAxes(i-1));
      storeImageShape(0) = axisSize;
   }
}


void LatticeStatsBase::stretchMinMax (Float& dMin, 
                                      Float& dMax)
{
   Float delta = 0.05*(dMax-dMin);
   Float absmax = max(abs(dMax),abs(dMin));
   if (delta < 1.0e-5*absmax) delta = 0.01 * absmax;

   if (dMin==dMax) {
      if (dMin==0.0) {
         dMin = -1.0; 
         dMax = 1.0;
      }
      else {
         dMin = dMin - 0.05*dMin; 
         dMax = dMax + 0.05*dMax;
      }
   }
   else {
      dMin = dMin - delta; 
      dMax = dMax + delta;
   }
}



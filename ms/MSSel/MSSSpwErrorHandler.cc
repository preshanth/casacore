//# MSSSpwErrorHandler.cc: Error handler for the SPW parser
//# Copyright (C) 1994,1995,1996,1997,2000
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
//#        Internet email: casa-feedback@nrao.edu.
//#        Postal address: AIPS++ Project Office
//#                        National Radio Astronomy Observatory
//#                        520 Edgemont Road
//#                        Charlottesville, VA 22903-2475 USA

#include <casacore/ms/MSSel/MSSSpwErrorHandler.h>
#include <casacore/ms/MSSel/MSSelectionError.h>
#include <casacore/casa/Arrays/Vector.h>
#include <vector>

namespace casacore { //# NAMESPACE CASACORE - BEGIN

  String MSSSpwErrorHandler::constructMessage()
  {
    ostringstream Mesg;
    if (messageList.size() > 0)
      {
	Mesg << messageList[0];
	if (tokenList.size() > 0)
	  for (uInt i=0;i<tokenList.size();i++) Mesg << tokenList[i] << " ";
	else
	  for (uInt i=1;i<messageList.size(); i++) Mesg << endl << messageList[i];
      }
    String casaMesg(Mesg.str());
    return casaMesg;
  }

  void MSSSpwErrorHandler::handleError(MSSelectionError&  mssErrorType) 
  {
    if (messageList.size() > 0)
      {
	String mesg(constructMessage());
	mssErrorType.addMessage(mesg);
	LogIO logIO;
	logIO << mssErrorType.getMesg() << LogIO::WARN << LogIO::POST;
      }
  }

} //# NAMESPACE CASACORE - END


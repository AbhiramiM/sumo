/****************************************************************************/
// Eclipse SUMO, Simulation of Urban MObility; see https://eclipse.org/sumo
// Copyright (C) 2017-2017 German Aerospace Center (DLR) and others.
// TraaS module
// Copyright (C) 2016-2017 Dresden University of Technology
/****************************************************************************/
//
//   This program and the accompanying materials
//   are made available under the terms of the Eclipse Public License v2.0
//   which accompanies this distribution, and is available at
//   http://www.eclipse.org/legal/epl-v20.html
//
/****************************************************************************/
/// @file    SumoNextTLS.java
/// @author  Mario Krumnow
/// @author  Evamarie Wiessner
/// @date    2016
/// @version $Id$
///
//
/****************************************************************************/
package de.tudresden.ws.container;

import java.util.LinkedList;

/**
 * 
 * @author Mario Krumnow
 *
 */

public class SumoNextTLS implements SumoObject {

	public LinkedList<NextTLS> ll;
	
	public SumoNextTLS(){
		this.ll = new LinkedList<NextTLS>();
	}
	
	public void add(String tlsID, int ix, double dist, String state){
		this.ll.add(new NextTLS(tlsID, ix, dist, state));
	}
	
	public String toString(){
		
		return "";
		//return this.phasedef+"#"+this.duration+"#"+this.duration1+"#"+this.duration2;
	}
	
	public class NextTLS{
		
		public String tlsID;
		int ix;
		double dist;
		String state;
		
		public NextTLS(String tlsID, int ix, double dist, String state){
			this.tlsID = tlsID;
			this.ix = ix;
			this.dist = dist;
			this.state = state;
		}
	}
	
	
}
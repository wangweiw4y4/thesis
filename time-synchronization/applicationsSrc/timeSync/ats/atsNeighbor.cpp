#include "atsNeighbor.h"

#include "world.h"
#include "lattice.h"

#include "../simulation.h"

//#define ATS_LINEAR_REGRESSION

namespace Synchronization {

  // ATSNeighbor class
  
  ATSNeighbor::ATSNeighbor() {
    rtt_T1 = 0;
    relativeSkew = 1.0;
    pOld = Point(0,0);
    round = 0;
  }

  ATSNeighbor::ATSNeighbor(const ATSNeighbor &n): rtt_T1(n.rtt_T1), relativeSkew(n.relativeSkew), pOld(n.pOld), round(n.round), points(n.points) {
  
  }

  ATSNeighbor::~ATSNeighbor() {

  }

  void ATSNeighbor::updateRelativeSkew(Point &pNew) {
    myDouble_t p = ATS_RELATIVE_SKEW_UPDATE;
    myDouble_t rskew = 0;
    
#ifdef ATS_LINEAR_REGRESSION
    rskew = avgSkew();
#else 
    myDouble_t diffNum = ((myDouble_t) pNew.global) - ((myDouble_t) pOld.global);
    myDouble_t diffDen = ((myDouble_t) pNew.local) - ((myDouble_t) pOld.local);
    rskew = diffNum/diffDen;
#endif
    relativeSkew = relativeSkew*p + (1.0-p)*rskew;
  }


  // ATSNeighbors class
  
  ATSNeighbors::ATSNeighbors() {
    degree_t d = BaseSimulator::getWorld()->lattice->getMaxNumNeighbors();
    neighbors.resize(d);
  }

  ATSNeighbors::ATSNeighbors(const ATSNeighbors &n): neighbors(n.neighbors) {
  }
  
  ATSNeighbors::~ATSNeighbors() {

  }
  
  ATSNeighbor* ATSNeighbors::getATSNeighbor(P2PNetworkInterface *p2p) {
    degree_t index = p2p->hostBlock->getInterfaceIndex(p2p);
    return &neighbors[index];
  }

  void ATSNeighbor::add(Point p) {
#ifdef ATS_LINEAR_REGRESSION
    points.push_back(p);
    if (points.size() > ATS_POINT_NUM) {
      points.pop_back();
    }
#else
    pOld = p;
#endif
  }

  myDouble_t ATSNeighbor::avgSkew() {
    // x: local time
    // y: global time
    myDouble_t xAvg = 0, yAvg = 0;
    myDouble_t sum1 = 0, sum2 = 0;
    myDouble_t y0 = 1;
    
    if (points.size() == 0) {
      return 1.0;
    }
	
    if (points.size() == 1) {
      if (points.begin()->local != 0) {
	y0 = (myDouble_t)points.begin()->global / (myDouble_t)points.begin()->local;
      } else {
	y0 = 1;
      }
      return y0;
    }

    for (vector<Point>::iterator it = points.begin() ; it != points.end(); it++){
      xAvg += (myDouble_t)it->local;
      yAvg += (myDouble_t)it->global;
    }

    xAvg = xAvg/points.size();
    yAvg = yAvg/points.size();
    for (vector<Point>::iterator it = points.begin() ; it != points.end(); it++){
      sum1 += ((myDouble_t)it->local - xAvg) * ((myDouble_t)it->global - yAvg);
      sum2 += pow((myDouble_t)it->local - xAvg,2.0);
    }

    y0 = sum1/sum2;
    return y0;
  } 
}

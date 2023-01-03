#ifndef _hgcssfirsthadint_hh_
#define _hgcssfirsthadint_hh_


#include <iomanip>
#include <vector>
#include "Rtypes.h"
#include <sstream>
#include <iostream>
#include <map>
#include <cmath>
#include "TMath.h"



class HGCSSFirstHadInt{


public:
  HGCSSFirstHadInt():    
    event_(0),
    foundHadInt_(0),
    process_(0),
    x_(0),
    y_(0),
    z_(0),
    nsec_(0),
    sec_pdgID_(0),
    sec_charge_(0),
    sec_kin_(0),
    parent_id_(100),
    track_id_(100)
  {

  };



  virtual ~HGCSSFirstHadInt(){};
//getters
  inline int event() const {
      return event_;
    };

  inline bool foundHadInt() const {
      return foundHadInt_;
    };
  
  inline int process() const {
      return process_;
    };

  inline double x() const {
      return x_;
    };

  inline double y() const {
      return y_;
    };

  inline double z() const {
      return z_;
    };
  
  inline int nsec() const {
      return nsec_;
    };
  
  inline double sec_pdgID() const {
      return sec_pdgID_;
    };
  
  inline double sec_charge() const {
      return sec_charge_;
    };
  
  inline double sec_kin() const {
      return sec_kin_;
    };

  inline double parent_id() const {
      return parent_id_;
    };

  inline double track_id() const {
      return track_id_;
    };


//setters

  inline void event(const int & val) {
      event_ = val;
    };

  inline void foundHadInt(const bool & val){
      foundHadInt_ = val;
    };

  inline void process(const int & val){
      process_ = val;
    };

  inline void x(const double & val){
      x_ = val;
    };

  inline void y(const double & val){
      y_ = val;
    };

  inline void z(const double & val){
      z_ = val;
    };

  inline void nsec(const int & val){
      nsec_ = val;
    };

  inline void sec_pdgID(const double & val){
      sec_pdgID_ = val;
    };

  inline void sec_charge(const double & val){
      sec_charge_ = val;
    };

  inline void sec_kin(const double & val){
      sec_kin_ = val;
    };

  inline void parent_id(const double & val){
      parent_id_ = val;
    };

  inline void track_id(const double & val){
      track_id_ = val;
    };




private:

  int event_;
  bool foundHadInt_;
  int process_;
  double x_;
  double y_;
  double z_;
  int nsec_;
  double sec_pdgID_;
  double sec_charge_;
  double sec_kin_;
  double parent_id_;
  double track_id_;


  ClassDef(HGCSSFirstHadInt,1);



};

typedef std::vector<HGCSSFirstHadInt> HGCSSFirstHadIntVec;


#endif

#ifndef _hgcsspi0info_hh_
#define _hgcsspi0info_hh_


#include <iomanip>
#include <vector>
#include "Rtypes.h"
#include <sstream>
#include <iostream>
#include <map>
#include <cmath>
#include "TMath.h"



class HGCSSpi0Info{


public:
  HGCSSpi0Info():
    process_(0),
    x_(0),
    y_(0),
    z_(0),
    particle_pdgID_(0),
    particle_charge_(0),
    particle_kin_(0),
    parent_id_(0),
    track_id_(0)
  {

  };



  virtual ~HGCSSpi0Info(){};
//getters

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

  inline double particle_pdgID() const {
      return particle_pdgID_;
    };

  inline double particle_charge() const {
      return particle_charge_;
    };

  inline double particle_kin() const {
      return particle_kin_;
    };

  inline double parent_id() const {
      return parent_id_;
    };

  inline double track_id() const {
      return track_id_;
    };


//setters

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

  inline void particle_pdgID(const double & val){
      particle_pdgID_ = val;
    };

  inline void particle_charge(const double & val){
      particle_charge_ = val;
    };

  inline void particle_kin(const double & val){
      particle_kin_ = val;
    };

  inline void parent_id(const double & val){
      parent_id_ = val;
    };

  inline void track_id(const double & val){
      track_id_ = val;
    };





private:

  int process_;
  double x_;
  double y_;
  double z_;
  double particle_pdgID_;
  double particle_charge_;
  double particle_kin_;
  double parent_id_;
  double track_id_;


  ClassDef(HGCSSpi0Info,1);


};

typedef std::vector<HGCSSpi0Info> HGCSSpi0InfoVec;

#endif

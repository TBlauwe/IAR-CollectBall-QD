#ifndef _INCLUDES_HPP_
#define _INCLUDES_HPP_

/***
  includes.hpp : All necessary includes and defines
 ***/

// Program variants are defined by a set of labels described below:

// these are the default, no need to specify it anymore

#define TRAJECTORY

enum diversity_measure_t {multi=-1, adhoc=0, hamming,trajectory, entropy, nb_measures};

typedef enum _fit_id{ ballcount,  nb_fit } Fit_id;

#define NB_TILES 12.0

//switch color
#define SWITCH 4

// ball color
#define BALL 3    

//basket color
#define BASKET 2

// To avoid problems between SDL and multithreading
#if defined(APPLE) || defined(VISU)
    #define NO_PARALLEL
#endif

#ifdef NO_PARALLEL
    #warning no parallel.
#endif

#ifndef EIGEN3_ENABLED
    #error "Eigen3 must be enabled for this experiment"
#endif

#include <Eigen/Core>

#include <iostream>
#include <bitset>
#include <limits>
#include <sferes/phen/parameters.hpp>

#ifdef USE_SDL
    #include <SDL.h>
#endif


#include <modules/nn2/mlp.hpp>
#include <modules/nn2/phen_dnn.hpp>
#include <modules/nn2/elman.hpp>

#include "custom_run.hpp"           
#include <sferes/stc.hpp>
#include <sferes/misc.hpp>

#ifndef SAMPLEDPARAMS
    #include <sferes/gen/evo_float.hpp>
#else
    #include <sferes/gen/sampled.hpp>
#endif

#include <sferes/modif/dummy.hpp>
#include <sferes/eval/parallel.hpp>
#include <sferes/eval/eval.hpp>
#include <sferes/stat/pareto_front.hpp>
#include <sferes/stat/best_fit.hpp>

#include <modules/fastsim/simu_fastsim.hpp>


using namespace sferes;

#ifndef SAMPLEDPARAMS
    using namespace sferes::gen::evo_float;
#endif

using namespace sferes::gen::dnn;

// Any other definition of point_type is possible, not necessary the trajectory
struct point_traj
{
    int x,y;
    bool ball;
    bool operator==(const struct point_traj &op) const {return x==op.x && y==op.y; } //&& eqball(op); }
    bool eqball(const struct point_traj &op) const {return ball^op.ball;}
    float operator-(const struct point_traj &op) const {return (abs(x-op.x)+abs(y-op.y))*1.0/NB_TILES; } //+NB_TILES*eqball(op); }
};

#include "fit_collectball_qd.hpp"
#include "behavior_dist.hpp"

// =============== Misc ===============   
#include <cmath>

// =============== Boost ===============   
#include <boost/foreach.hpp>
#include <boost/multi_array.hpp>
#include <boost/array.hpp>
#include <boost/fusion/algorithm/iteration/for_each.hpp>
#include <boost/fusion/include/for_each.hpp>

// ============== Modular QD ================
#include <exp/modular_QD/quality_diversity.hpp>
#include <exp/modular_QD/selector.hpp>
#include <exp/modular_QD/container.hpp>
#include <exp/modular_QD/stat.hpp>

#endif

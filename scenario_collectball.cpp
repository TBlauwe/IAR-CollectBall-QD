#include "includes.hpp"             // Sferes & other includes -- SEE THIS FILE FOR PROGRAM VARIANTS
// also include entropy_distance.hpp
//              edit_distance.hpp
//              modifier_behavior.hpp
#include "defparams.hpp"            // Params
#include "defstats.hpp"             // Define all stats
#include "definitsimu.hpp"          // Simulation initialization

std::string res_dir="not_initialized";

// ****************** Main *************************
int main(int argc, char **argv)
{
    srand(time(0));

    using namespace sferes;

    typedef eval::Parallel<Params> eval_t;

    typedef boost::fusion::vector<
        sferes::stat::Container<phen_t, Params>
#ifdef FILIATION
        ,sferes::stat::Filiation<phen_t, Params>
#endif
        ,sferes::stat::Progress<phen_t, Params>
#ifdef TRACELOG
        ,sferes::stat::TraceLog<phen_t, Params>
#endif
        >  stat_t;

    //MODIFIER
    typedef boost::fusion::vector<
#if defined (DYNAMIC_DIVERSITY) || defined(DIV_BEHAVIOR)
        modif::Modifier_DD<Params>
#elif defined(NOV_BEHAVIOR) 
        modif::BehaviorNov<Params>  
#else
        modif::Dummy<Params>
#endif
        > modifier_t;


#if defined(GRID)
    typedef container::Grid<phen_t, Params> container_t;
#else // ARCHIVE
    typedef container::Archive<phen_t, Params> container_t;
#endif


#if defined(RANDOM)
    typedef selector::Random<phen_t> select_t;
#elif defined(FITNESS)
    typedef selector::ScoreProportionate<phen_t,selector::getFitness> select_t;
#elif defined(NOVELTY)
    typedef selector::ScoreProportionate<phen_t,selector::getNovelty> select_t;
#elif defined(CURIOSITY)
    typedef selector::ScoreProportionate<phen_t,selector::getCuriosity> select_t;
#elif defined(POPFITNESS)
    typedef selector::PopulationBased<phen_t, selector::ScoreProportionate<phen_t, selector::getFitness> > select_t;
#elif defined(POPNOVELTY)
    typedef selector::PopulationBased<phen_t, selector::ScoreProportionate<phen_t, selector::getNovelty> > select_t;
#elif defined(POPCURIOSITY)
    typedef selector::PopulationBased<phen_t, selector::ScoreProportionate<phen_t, selector::getCuriosity> > select_t;
#elif defined(TOURFITNESS)
    typedef selector::TournamentBased<phen_t,selector::getFitness> select_t;
#elif defined(TOURNOVELTY)
    typedef selector::TournamentBased<phen_t,selector::getNovelty> select_t;
#elif defined(TOURCURIOSITY)
    typedef selector::TournamentBased<phen_t,selector::getCuriosity> select_t;
#elif defined(PARETO) //NSLC
    typedef selector::ParetoBased<phen_t,boost::fusion::vector<selector::getNovelty,selector::getLocalQuality>, Params > select_t;
#else // NOSELECTION
    typedef selector::NoSelection<phen_t> select_t;

#endif

    typedef ea::QualityDiversity<phen_t, eval_t, stat_t, modifier_t, select_t, container_t, Params> ea_t;

    ea_t ea;

    try {
        std::cout<<"start"<<std::endl;
        res_dir=ea.res_dir();
        ea.run();
        std::cout<<"end"<<std::endl;
    }
    catch(fastsim::Exception e) {
        std::cerr<<"fastsim::Exception: "<<e.get_msg()<<std::endl;
    }
    return 0;

}

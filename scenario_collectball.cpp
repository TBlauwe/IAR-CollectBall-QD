#include "includes.hpp"             // Sferes & other includes -- SEE THIS FILE FOR PROGRAM VARIANTS
                                    // also include entropy_distance.hpp
                                    //              edit_distance.hpp
                                    //              modifier_behavior.hpp
#include "defparams.hpp"            // Params
#include "defstats.hpp"            // Params
#include "definitsimu.hpp"          // Simulation initialization

#include "custom_run.hpp"           // Simulation initialization

// ****************** Main *************************
int main(int argc, char **argv)
{
    using namespace sferes;

    // ===== EVAL =====
    typedef eval::Parallel<Params> eval_t;

    // ===== STAT ===== 
    typedef boost::fusion::vector<
        sferes::stat::BestFitVal<phen_t, Params>
        ,sferes::stat::Progress<phen_t, Params>
        ,sferes::stat::Selection<phen_t, Params>
#ifdef TRACELOG
        ,sferes::stat::TraceLog<phen_t, Params>
#endif
        >  stat_t;

    // ===== MODIFIER =====
    typedef modif::Dummy<> modifier_t;



    // ===== CONTAINER =====
#if defined(GRID)
    typedef selector::Grid<phen_t> select_t;
#else
    typedef container::Archive<phen_t, Params> container_t;
#endif


    // ===== SELECTOR =====
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
#else // NOSELECTION
    typedef selector::NoSelection<phen_t> select_t;
#endif

    typedef ea::QualityDiversity<phen_t, eval_t, stat_t, modifier_t, select_t, container_t, Params> ea_t;
    ea_t ea;

    // Building result's dir
    const std::string path(argv[0]);
    auto const pos=path.find_last_of('/');
    const auto program_name=path.substr(pos+1);

    ea.set_res_dir("results/" + program_name + "_" + misc::date());

    std::cout <<"             path : "<< path <<std::endl;

    try {
        custom_run_ea(argc, argv, ea, fit_t());
    }
    catch(fastsim::Exception e) {
        std::cerr<<"fastsim::Exception: "<<e.get_msg()<<std::endl;
    }
    return 0;
}


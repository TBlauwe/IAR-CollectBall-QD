#include "includes.hpp"             // Sferes & other includes -- SEE THIS FILE FOR PROGRAM VARIANTS
                                    // also include entropy_distance.hpp
                                    //              edit_distance.hpp
                                    //              modifier_behavior.hpp
#include "defparams.hpp"            // Params
#include "defstats.hpp"             // Define all stats
#include "definitsimu.hpp"          // Simulation initialization
#include "fit_collectball_qd.hpp"   // Fitness function


std::string res_dir="not_initialized";


// ****************** Main *************************
int main(int argc, char **argv)
{
    srand(time(NULL));
    tbb::task_scheduler_init init(20);  

    using namespace sferes;

    typedef FitCollectBallQD<Params> fit_t;

    typedef gen::EvoFloat<8, Params> gen_t;
    typedef phen::Parameters<gen_t, fit_t, Params> phen_t;
    typedef eval::Parallel<Params> eval_t;

    typedef modif::Dummy<> modifier_t;

#if defined(GRID)
    typedef container::Grid<phen_t, Params> container_t;
#else // ARCHIVE
    typedef container::Archive<phen_t, Params> container_t;
#endif

    typedef boost::fusion::vector<stat::Container<phen_t, Params>,stat::Progress<phen_t, Params> > stat_t;

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
    ea.run();
}

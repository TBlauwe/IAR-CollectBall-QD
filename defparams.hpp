#ifndef _DEFPARAMS_HPP_
#define _DEFPARAMS_HPP_

using namespace sferes::gen::evo_float;

struct Params
{

    struct nov{
        SFERES_CONST size_t deep=3; //7x7
        SFERES_CONST size_t k=15;
        SFERES_CONST double l=0.01;
        SFERES_CONST double eps=0.1;

    };

    struct ea
    {
        SFERES_CONST size_t behav_dim = 2;
        SFERES_ARRAY(size_t, behav_shape, 100, 100);

    };

    struct pareto
    {
        SFERES_CONST bool genoDiv =true;
    };

    struct dnn
    {

        static constexpr size_t nb_inputs       = 3+2+2+2+2+1; // SIMPLE MODE :static constexpr size_t nb_inputs       = 3+2+2+2+1;
        static constexpr size_t nb_outputs      = 3;
        static constexpr size_t min_nb_neurons  = 10;
        static constexpr size_t max_nb_neurons  = 30;
        static constexpr size_t min_nb_conns    = 50;
        static constexpr size_t max_nb_conns    = 250;

        static constexpr int io_param_evolving = true;
#if defined(SETUP2)
        static constexpr float m_rate_add_conn	= 0.01f;
        static constexpr float m_rate_del_conn	= 0.002f;
        static constexpr float m_rate_change_conn = 0.001f;
        static constexpr float m_rate_add_neuron  = 0.002f;
        static constexpr float m_rate_del_neuron  = 0.001f;
#elif defined(SETUP1)
        static constexpr float m_rate_add_conn	= 0.30f;
        static constexpr float m_rate_del_conn	= 0.01f;
        static constexpr float m_rate_change_conn = 0.10f;
        static constexpr float m_rate_add_neuron  = 0.10f;
        static constexpr float m_rate_del_neuron  = 0.01f;
#elif defined(SETUPFF)
        static constexpr float m_rate_add_conn	= 0.0f;
        static constexpr float m_rate_del_conn	= 0.0f;
        static constexpr float m_rate_change_conn = 0.05f;
        static constexpr float m_rate_add_neuron  = 0.0f;
        static constexpr float m_rate_del_neuron  = 0.0f;
#else
        static constexpr float m_rate_add_conn	= 0.15f;
        static constexpr float m_rate_del_conn	= 0.05f;
        static constexpr float m_rate_change_conn = 0.03f;
        static constexpr float m_rate_add_neuron  = 0.05f;
        static constexpr float m_rate_del_neuron  = 0.05f;
#endif
        static constexpr init_t init = ff;
    };

#ifdef SAMPLEDPARAMS
    struct sampled 
    {
        SFERES_ARRAY(float, values,
                0.0f, 0.05f, 0.1f, 0.15f, 0.2f, 0.25f, 0.3f, 
                0.35f, 0.4, 0.45f, 0.55f, 0.6, 0.65f,
                0.7f, 0.75f, 0.8f, 0.85f, 0.9f, 0.95f, 1.0f); 

        static constexpr float mutation_rate = 0.1f;
        static constexpr float cross_rate = 0.0f;    
        static constexpr bool ordered = true;
    };

#else
    struct evo_float
    {
        static constexpr mutation_t mutation_type = polynomial;
        static constexpr cross_over_t cross_over_type = sbx;
        //static constexpr cross_over_t cross_over_type = no_cross_over;
        static constexpr float cross_rate = 0.0f;    
        static constexpr float mutation_rate = 0.1f;
        static constexpr float eta_m = 15.0f;
        static constexpr float eta_c = 10.0f;
    };
#endif

    struct pop
    {

#ifdef DEBUG
        static constexpr unsigned size = 8;
#else
        static constexpr unsigned size = 200;
#endif

        // number of generations
#ifdef NOSTOP
        static constexpr unsigned nb_gen = 20001;
#elif defined DEBUG
        static constexpr unsigned nb_gen = 201;
#else
        static constexpr unsigned nb_gen = 4001; //RESET 5001
#endif

        static constexpr int dump_period = 50;
    };

    struct simu
    { 
        static constexpr int laser_range     = 100.0f;
        //Evalutations
        static constexpr float nb_steps = 12000;

        SFERES_STRING(map_name, SFERES_ROOT "/exp/modular_QD/scenarii/collectball/arena2.pbm");
        SFERES_STRING(alt_map_name, SFERES_ROOT "/exp/modular_QD/scenarii/collectball/arena2b.pbm");
    };

    struct fitness
    {
        static constexpr unsigned int nb_step_watch=4000; // diversity/novelty computed on nb_step_watch number of steps 
        static constexpr unsigned int step_sample = 1; // steps between samples (diversity/novelty)
        static constexpr unsigned int nb_io = Params::dnn::nb_inputs+Params::dnn::nb_outputs; 
        static constexpr unsigned int nb_bits=nb_io;
        static constexpr unsigned int nb_caracs = 9;
        static constexpr unsigned int sampling_rate = 10;
    };

    struct parameters
    {
        static constexpr float min_2 = 0.0f;
        static constexpr float max_2 = 5.0f;

#if defined(LOWPARAMS)
        static constexpr float min = -1.0f;
        static constexpr float max = 1.0f;
#else
        static constexpr float min = -5.0f;
        static constexpr float max = 5.0f;
#endif
    };
};

using namespace nn;
typedef FitCollectBallQD<Params> fit_t;

#ifndef SAMPLEDPARAMS
typedef phen::Parameters<gen::EvoFloat<1, Params>, fit::FitDummy<>, Params> weight_t;
typedef phen::Parameters<gen::EvoFloat<1, Params>, fit::FitDummy<>, Params> bias_t;
#else
typedef phen::Parameters<gen::Sampled<1, Params>, fit::FitDummy<>, Params> weight_t;
typedef phen::Parameters<gen::Sampled<1, Params>, fit::FitDummy<>, Params> bias_t;
#endif

typedef PfWSum<weight_t> pf_t;
typedef phen::Parameters<gen::EvoFloat<4, Params>, fit::FitDummy<>, Params> node_label_t;
typedef AfSigmoidBias<bias_t> af_t; 
typedef Neuron<pf_t, af_t >  neuron_t;
typedef Connection <weight_t> connection_t;
typedef gen::Dnn< neuron_t, connection_t, Params> gen_t;
typedef phen::Dnn<gen_t, fit_t, Params> phen_t;

#endif

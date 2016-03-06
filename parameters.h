#pragma once

enum OptionPayoffType
{
    Call,
    Put,
};

enum OptionExerciseType
{
    European,
    American,
};

enum JumpType
{
    None,
    Merton,
    Kou,
    CGMY,
};

struct Parameters
{
    Parameters();

    // Symbol: S
    double startPrice;

    // Symbol: K
    double strikePrice;

    // Symbol: r
    double riskFreeRate;

    // Symbol: q
    // Continuous dividend rate.
    double dividendRate;

    // Symbol: T
    double expiryTime;

    // Symbol: σ (sigma)
    double volatility;

    // Symbol: x_min and x_max
    double x_min();
    double x_max();

    // Symbol: N
    unsigned int resolution;

    // Number of timesteps to perform (number of times to go to fourier
    // space and back). For European options, this does not need to be
    // greater than one.
    unsigned int timesteps;

    // Symbol: delta t
    double timeIncrement();

    // Put or Call
    OptionPayoffType optionPayoffType;

    // European or American
    OptionExerciseType optionExerciseType;

    // ---- Jump specific parameters -----

    // Symbol: λ (lambda)
    // Mean of the poisson distribution for jumps.
    double jumpMean;

    JumpType jumpType;

    // Symbol: κ (kappa)
    double kappa();

    // Symbol: γ (gamma) in Lippa (2013), \tilde{σ} in Surkov (2009)
    // Parameter used for Merton jump distribution, which models jumps
    // as a standard normal.
    //
    // Normally, this is σ (standard deviation) in the normal,
    // but here we already use σ for the volatility so we need
    // another variable name.
    //
    // In Surkov (2009), this is represented with
    double mertonNormalStdev;

    // Symbol: μ (mu)
    // Mean of the normal in Merton jump diffusion.
    double driftRate;

    // Parameters used for Kou jump diffusion, which is based on a
    // double exponential (a combination of two exponential to represent
    // up and down jumps).
    //
    // Symbols: p, η1, η2 in Lippa (2013)
    //          ηp, η+, η- in Surkov (2009)
    double kouUpJumpProbability;
    double kouUpRate;
    double kouDownRate;

    // CGMY
    double CGMY_C;
    double CGMY_G;
    double CGMY_M;
    double CGMY_Y;

    // ---- Misc -----
    //
    // Print more debug info.
    bool debug;
    bool verbose;

private:
    // Use x_min and x_max
    double logBoundary;
};

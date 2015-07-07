/****************************************************************************/
/// @file    MSSwarmTrafficLightLogic.h
/// @author  Gianfilippo Slager
/// @date    Mar 2010
/// @version $Id: MSSwarmTrafficLightLogic.h 0 2010-03-04 12:40:00Z gslager $
///
// The class for Swarm-based logics
/****************************************************************************/
// SUMO, Simulation of Urban MObility; see http://sumo.dlr.de/
// Copyright 2001-2009 DLR (http://www.dlr.de/) and contributors
/****************************************************************************/
//
//   This program is free software; you can redistribute it and/or modify
//   it under the terms of the GNU General Public License as published by
//   the Free Software Foundation; either version 2 of the License, or
//   (at your option) any later version.
//
/****************************************************************************/
#ifndef MSSwarmTrafficLightLogic_h
#define MSSwarmTrafficLightLogic_h

// ===========================================================================
// included modules
// ===========================================================================
#ifdef _MSC_VER
#include <windows_config.h>
#else
#include <config.h>
#endif

//#define SWARM_DEBUG
#include <utils/common/SwarmDebug.h>
#include "MSSOTLHiLevelTrafficLightLogic.h"
#include "MSSOTLPhasePolicy.h"
#include "MSSOTLPlatoonPolicy.h"
#include "MSSOTLMarchingPolicy.h"
#include "MSSOTLCongestionPolicy.h"
#include "MSSOTLPolicy5DFamilyStimulus.h"

class MSSwarmTrafficLightLogic: public MSSOTLHiLevelTrafficLightLogic {
public:


	//****************************************************

	/**
	 * @brief Constructor without sensors passed
     * @param[in] tlcontrol The tls control responsible for this tls
     * @param[in] id This tls' id
     * @param[in] subid This tls' sub-id (program id)
     * @param[in] phases Definitions of the phases
     * @param[in] step The initial phase index
     * @param[in] delay The time to wait before the first switch
	 * @param[in] parameters Parameters defined for the tll
	 */
	MSSwarmTrafficLightLogic(MSTLLogicControl &tlcontrol, const string &id,
			const string &subid, const Phases &phases, unsigned int step,
			SUMOTime delay,
			const std::map<std::string, std::string>& parameters);

	~MSSwarmTrafficLightLogic();

	/**
	 * @brief Initialises the tls with sensors on incoming and outgoing lanes
	 * Sensors are built in the simulation according to the type of sensor specified in the simulation parameter
	 * @param[in] nb The detector builder
	 * @exception ProcessError If something fails on initialisation
	 */
	void init(NLDetectorBuilder &nb) throw (ProcessError);

	int getMaxCongestionDuration() {
		std::ostringstream key;
		key << "MAX_CONGESTION_DUR";
		std::ostringstream def;
		def << "120";
		return (int) s2f(getParameter(key.str(), def.str()));
	}
	/*void setMaxCongestionDuration(unsigned int val) {
	 max_congestion_duration = val;
	 }*/

	double getPheroMaxVal() {
		std::ostringstream key;
		key << "PHERO_MAXVAL";
		std::ostringstream def;
		def << "10.0";
		return s2f(getParameter(key.str(), def.str()));
	}
	/*void setPheroMaxVal(double val) {
	 phero_maxval = val;
	 }*/
	double getBetaNo() {
		std::ostringstream key;
		key << "BETA_NO";
		std::ostringstream def;
		def << "0.99";
		return s2f(getParameter(key.str(), def.str()));
	}
	/*void setBetaNo(double val) {
	 beta_no = val;
	 }*/
	double getGammaNo() {
		std::ostringstream key;
		key << "GAMMA_NO";
		std::ostringstream def;
		def << "1.0";
		return s2f(getParameter(key.str(), def.str()));
	}
	/*void setGammaNo(double val) {
	 gamma_no = val;
	 }*/
	double getBetaSp() {
		std::ostringstream key;
		key << "BETA_SP";
		std::ostringstream def;
		def << "0.99";
		return s2f(getParameter(key.str(), def.str()));
	}
	/*void setBetaSp(double val) {
	 beta_sp = val;
	 }*/
	double getGammaSp() {
		std::ostringstream key;
		key << "GAMMA_SP";
		std::ostringstream def;
		def << "1.0";
		return s2f(getParameter(key.str(), def.str()));
	}
	/*void setGammaSp(double val) {
	 gamma_sp = val;
	 }*/
	double getChangePlanProbability() {
		std::ostringstream key;
		key << "CHANGE_PLAN_PROBABILITY";
		std::ostringstream def;
		def << "0.003";
		return s2f(getParameter(key.str(), def.str()));
	}
	/*void setChangePlanProbability(double val) {
	 change_plan_probability = val;
	 }*/
	double getThetaMax() {
		std::ostringstream key;
		key << "THETA_MAX";
		std::ostringstream def;
		def << "0.8";
		return s2f(getParameter(key.str(), def.str()));
	}
	/*void setThetaMax(double val) {
	 theta_max = val;
	 }*/
	double getThetaMin() {
		std::ostringstream key;
		key << "THETA_MIN";
		std::ostringstream def;
		def << "0.2";
		return s2f(getParameter(key.str(), def.str()));
	}
	/*void setThetaMin(double val) {
	 theta_min = val;
	 }*/

	double getThetaInit() {
			std::ostringstream key;
			key << "THETA_INIT";
			std::ostringstream def;
			def << "0.5";
			return s2f(getParameter(key.str(), def.str()));
		}
	double getLearningCox() {
		std::ostringstream key;
		key << "LEARNING_COX";
		std::ostringstream def;
		def << "0.0005";
		return s2f(getParameter(key.str(), def.str()));
	}
	/*void setLearningCox(double val) {
	 learning_cox = val;
	 }*/
	double getForgettingCox() {
		std::ostringstream key;
		key << "FORGETTING_COX";
		std::ostringstream def;
		def << "0.0005";
		return s2f(getParameter(key.str(), def.str()));
	}
	/*void setForgettingCox(double val) {
	 forgetting_cox = val;
	 }*/
	double getScaleFactorDispersionIn(){
		return scaleFactorDispersionIn;
	}

	double getScaleFactorDispersionOut(){
		return scaleFactorDispersionOut;
	}

	    /** @brief Returns the type of the logic as a string
     * @return The type of the logic
     */
    const std::string getLogicType() const {
        return "swarmBasedTrafficLogic";
    }
    /// @}
protected:

	/**
	 * \brief This pheronome is an indicator of congestion on input lanes.\n
	 * Its levels refer to the average speed of vehicles passing the input lane:
	 * the lower the speed the higher the pheromone.\n
	 * These levels are updated on every input lane, independently on lights state.
	 */
	MSLaneId_PheromoneMap pheromoneInputLanes;

	/**
	 * \brief This pheromone is an indicator of congestion on output lanes.\n
	 * Its levels refer to the average speed of vehicles passing the output lane:
	 * the lower the speed the higher the pheromone.\n
	 * These levels are updated on every output lane, independently on lights state.
	 */
	MSLaneId_PheromoneMap pheromoneOutputLanes;

	/**
	 * This member keeps track of the last thresholds update, s.t.
	 * updates can be correctly performed even on time-variable interations.
	 * @see MSSwarmTrafficLightLogic::updateSensitivities()
	 */
	SUMOTime lastThetaSensitivityUpdate;

	/*
	 * This member has to contain the switching logic for SOTL policies
	 */

	size_t decideNextPhase();

	bool canRelease();

	/*
	 * Computes how much time will pass after decideNextPhase will be executed again
	 */
	virtual SUMOTime computeReturnTime() {

		return DELTA_T;

	}

	/**
	 * @brief Resets pheromone levels
	 */
	void resetPheromone();

	/*
	 * @return The average pheromone level regarding congestion on input lanes
	 */
	double getPheromoneForInputLanes();

	/*
	 * @return The average pheromone level regarding congestion on output lanes
	 */
	double getPheromoneForOutputLanes();

	/*
	 * @return The dispersion level regarding congestion on input lanes
	 */
	double getDispersionForInputLanes(double average_phero_in);

	/*
	 * @return The dispersion level regarding congestion on output lanes
	 */
	double getDispersionForOutputLanes(double average_phero_out);

	/*
	 * @return The difference between the current max phero value and the average phero of the other lanes
	 */
	double getDistanceOfMaxPheroForInputLanes();

	/*
	 * @return The difference between the current max phero value and the average phero of the other lanes
	 */
	double getDistanceOfMaxPheroForOutputLanes();
	/**
	 * @brief Update pheromone levels
	 * Pheromone on input lanes is costantly updated
	 * Pheromone follows a discrete-time dynamic law "pheromone(k+1) = beta*pheromone(k) + gamma * sensed_val(k)"
	 */
	void updatePheromoneLevels();

	/**
	 * After a policy has been chosen, for every iteration thresholds has to be updated.
	 * Thresholds reinforcement lowers the theta_sensitivity for the current policy and raises the ones for currently unused policies.
	 * Thresholds belongs to the interval [THETA_MIN THETA_MAX]
	 */
	void updateSensitivities();

	/**
	 * @brief Decide the current policy according to pheromone levels
	 * The decision reflects on currentPolicy value
	 */
	void decidePolicy();

	void choosePolicy(double phero_in, double phero_out, double dispersion_in, double dispersion_out);
	void choosePolicy(double phero_in, double phero_out);

	std::string getPoliciesParam() {
		std::ostringstream key;
		key << "POLICIES";
		std::ostringstream def;
		def << "Platoon;Phase;Marching;Congestion";
		return getParameter(key.str(), def.str());
	}

	void initScaleFactorDispersionIn(int lanes_in){
		std::vector<double> phero_values;

		for(int i=0; i<lanes_in/2; i++){
			phero_values.push_back(getPheroMaxVal());
		}
		for(int i=lanes_in/2; i<lanes_in; i++){
					phero_values.push_back(0.0);
		}

		double sum_avg_tmp = 0;

		for(int i=0; i<phero_values.size(); i++){
					sum_avg_tmp += phero_values[i];
		}

		double mean = sum_avg_tmp / phero_values.size();

		double sum_dev_tmp = 0;
		for(int i=0; i<phero_values.size(); i++){
					sum_dev_tmp += pow(phero_values[i] - mean, 2);
		}

		double deviation = sqrt(sum_dev_tmp/ phero_values.size());

		scaleFactorDispersionIn = getPheroMaxVal() / deviation;
	}

	void initScaleFactorDispersionOut(int lanes_out){
		std::vector<double> phero_values;

				for(int i=0; i<lanes_out/2; i++){
					phero_values.push_back(getPheroMaxVal());
				}
				for(int i=lanes_out/2; i<lanes_out; i++){
							phero_values.push_back(0.0);
				}

				double sum_avg_tmp = 0;
				for(int i=0; i<phero_values.size(); i++){
							sum_avg_tmp += phero_values[i];
				}
				double mean = sum_avg_tmp / phero_values.size();

				double sum_dev_tmp = 0;

				for(int i=0; i<phero_values.size(); i++){
							sum_dev_tmp += pow(phero_values[i] - mean, 2);
				}

				double deviation = sqrt(sum_dev_tmp/ phero_values.size());

				scaleFactorDispersionOut = getPheroMaxVal() / deviation;
	}
	bool logData;
	ofstream swarmLogFile;
	/**
	 * \brief When true, indicates that the current policy MUST be changed.\n
	 * It's used to force the exit from the congestion policy
	 */
	bool mustChange;
	unsigned int congestion_steps;

	/**
	 * \factors to scale pheromoneDispersion in range [0, 10]
	 */
	double scaleFactorDispersionIn;
	double scaleFactorDispersionOut;
};

#endif
/****************************************************************************/

#ifndef SHARK_OBJECTIVEFUNCTIONS_ABSTRACTOBJECTIVEFUNCTION_H
#define SHARK_OBJECTIVEFUNCTIONS_ABSTRACTOBJECTIVEFUNCTION_H


namespace shark {

template<typename PointType, typename ResultT> 
class AbstractObjectiveFunction : public INameable {
 public:
 	typedef PointType SearchPointType; 
 	typedef ResultT ResultType; 

 	// if the result type is not an arithmetic type, we assume it is a vector-type->multi objective optimization	
 	typedef typename boost::mpl::if<
 			std::is_arithmeti<ResultT>, 
 			SearchType, 
 			RealMatrix
 		>::type FirstOrderDerivative; 


 	struct SecondDerivative {
 		FirstOrderDerivative gradient; 
 		RealMatrix hessian;
 	};

 	enum Feature {
		HAS_VALUE						 =  1, ///< The function can be evaluated and evalDerivative returns a meaningless value (for example std::numeric_limits<double>::quiet_nan()).
		HAS_FIRST_DERIVATIVE             =  2, ///< The method evalDerivative is implemented for the first derivative and returns a sensible value.
		HAS_SECOND_DERIVATIVE            =  4, ///< The method evalDerivative is implemented for the second derivative and returns a sensible value.
		CAN_PROPOSE_STARTING_POINT       = 8, ///< The function can propose a sensible starting point to search algorithms.
		IS_CONSTRAINED_FEATURE           =  16, ///< The objective function is constrained.
		HAS_CONSTRAINT_HANDLER           =  32, ///< The constraints are governed by a constraint handler which can be queried by getConstraintHandler()
		CAN_PROVIDE_CLOSEST_FEASIBLE     = 64,	///< If the function is constrained, the method closestFeasible is implemented and returns a "repaired" solution.
		IS_THREAD_SAFE     = 128,	///< can eval or evalDerivative be called in parallel?
		IS_NOISY     = 256	///< The function value is perturbed by some kind of noise
	};


	// this defines the member m_features. Core/Flags.h 
	SHARK_FEATURE_INTERFACE; 

	bool hasValue() const {
		return m_features & HAS_VALUE;
	}

	// 
	bool hasFirstDerivative() const {
		return m_features & HAS_FIRST_DERIVATIVE;
	}


	bool hasSecondDerivative()const{
		return m_features & HAS_SECOND_DERIVATIVE;
	}
	
	/// \brief returns whether this function can propose a starting point.
	bool canProposeStartingPoint()const{
		return m_features & CAN_PROPOSE_STARTING_POINT;
	}
	
	/// \brief returns whether this function can return 
	bool isConstrained()const{
		return m_features & IS_CONSTRAINED_FEATURE;
	}
	
	/// \brief returns whether this function can return 
	bool hasConstraintHandler()const{
		return m_features & HAS_CONSTRAINT_HANDLER;
	}
	
	/// \brief Returns whether this function can calculate thee closest feasible to an infeasible point.
	bool canProvideClosestFeasible()const{
		return m_features & CAN_PROVIDE_CLOSEST_FEASIBLE;
	}
	
	/// \brief Returns true, when the function can be usd in parallel threads.
	bool isThreadSafe()const{
		return m_features & IS_THREAD_SAFE;
	}
	
	/// \brief Returns true, when the function can be usd in parallel threads.
	bool isNoisy()const{
		return m_features & IS_NOISY;
	}

	AbstractObjectiveFunction()
		: m_evaluationCounter(0)
	{
		m_features |= HAS_VALUE;
	}

	virtual AbstractObjectiveFunction() {}

	
};


}

#endif
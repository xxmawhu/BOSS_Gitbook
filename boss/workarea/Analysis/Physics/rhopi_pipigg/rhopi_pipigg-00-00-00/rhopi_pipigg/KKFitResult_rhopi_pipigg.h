#ifndef Physics_Analysis_KKFitResult_rhopi_pipigg_H
#define Physics_Analysis_KKFitResult_rhopi_pipigg_H

/// @addtogroup BOSS_objects
/// @{

/**
 * @brief    Derived class for a container that contains important fit results of the `KalmanKinematicFit`, including masses.
 * @author   Remco de Boer 雷穆克 (r.e.deboer@students.uu.nl or remco.de.boer@ihep.ac.cn)
 * @date     December 14th, 2018
 */



// * ========================= * //
// * ------- LIBRARIES ------- * //
// * ========================= * //

	#include "TrackSelector/KKFitResult.h"
	#include "TrackSelector/TrackSelector.h"
	#include "McTruth/McParticle.h"



// * ================================ * //
// * ------- CLASS DEFINITION ------- * //
// * ================================ * //
class KKFitResult_rhopi_pipigg : public KKFitResult
{
public:
	// * CONSTRUCTORS * //
		KKFitResult_rhopi_pipigg() : fFitMeasure(1e9) {}
		KKFitResult_rhopi_pipigg(KalmanKinematicFit* kkmfit);
		KKFitResult_rhopi_pipigg(Event::McParticle* kaonNeg1, Event::McParticle* kaonNeg2, Event::McParticle* kaonPos, Event::McParticle* pionPos);

	// * INFORMATION * //
		bool IsBetter() const;

	// * PUBLIC DATA MEMBERS * //
		double fM_pi0;      //!< Current computed mass of the \f$\pi^0\f$ candidate.
		double fM_rho0;     //!< Current computed mass of the \f$\rho^0\f$ candidate.
		double fM_rhom;     //!< Current computed mass of the \f$\rho^-\f$ candidate.
		double fM_rhop;     //!< Current computed mass of the \f$\rho^+\f$ candidate.
		double fM_JpsiRho0; //!< Current computed mass of the \f$J/\psi \rightarrow \rho^0\pi^0\f$ candidate.
		double fM_JpsiRhom; //!< Current computed mass of the \f$J/\psi \rightarrow \rho^-\pi^+\f$ candidate.
		double fM_JpsiRhop; //!< Current computed mass of the \f$J/\psi \rightarrow \rho^+\pi^-\f$ candidate.
		double fFitMeasure;

private:
	void SetValues(KalmanKinematicFit* kkmfit);
	void SetValues(const HepLorentzVector &pKaonNeg1, const HepLorentzVector &pKaonNeg2, const HepLorentzVector &pKaonPos, const HepLorentzVector &pPionPos);
	void SetValues(Event::McParticle *kaonNeg1, Event::McParticle *kaonNeg2, Event::McParticle *kaonPos, Event::McParticle *pionPos);


};

/// @}


#endif
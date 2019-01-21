// * ========================= * //
// * ------- LIBRARIES ------- * //
// * ========================= * //

	#include "TrackSelector/CutObject.h"
	#include <float.h>
	#include <iostream>
	#include <iomanip>



// * =========================== * //
// * ------- CONSTRUCTOR ------- * //
// * =========================== * //

	CutObject::CutObject(const std::string &cutname, const std::string &cutdescription) :
		name(cutname),
		description(cutdescription),
		min(-DBL_MAX),
		max( DBL_MAX),
		counter(0)
	{
		instances.push_back(this);
	}
	CutObject::~CutObject() {
		instances.remove(this);
	}



// * =========================== * //
// * ------- INFORMATION ------- * //
// * =========================== * //

	/**
	 * @brief Print the `name`, `min` value, `max` value, and `counter` value of the cut object. If all arguments are set, the output will be print in table format.
	 * 
	 * @param wname    With of the `name` column
	 * @param wmin     With of the `min` column.
	 * @param wmax     With of the `max` column.
	 * @param wcounter With of the `counter` column.
	 */
	void CutObject::Print(const int wname, const int wmin, const int wmax, const int wcounter) const
	{
		/// -# Print a table line if required by `print`.
		if(wname && wmin && wmax && wcounter) {
			/// <ol>
			/// <li> Print cut name.
			std::cout << "  " << std::setw(wname) << std::left  << name;
			std::cout << " | ";
			/// <li> Print minimum if available.
			std::cout << std::setw(wmin) << std::right;
			if(min > -DBL_MAX) std::cout << min;
			else std::cout << "";
			std::cout << " | ";
			/// <li> Print maximum if available.
			std::cout << std::setw(wmax) << std::right;
			if(max < DBL_MAX) std::cout << max;
			else std::cout << "";
			std::cout << " | ";
			/// <li> Print counter if available.
			std::cout << std::setw(wcounter) << std::right << counter << std::endl;
			/// </ol>
		} else {
			// if only a min value
			if((min > -DBL_MAX) && (max ==  DBL_MAX)) {
				std::cout << name << " > " << min << "    " << counter << std::endl;
				return;
			}
			// if only a max value
			if((max <  DBL_MAX) && (min == -DBL_MAX)) {
				std::cout << name << " < " << max << "    " << counter << std::endl;
				return;
			}
			// if both min and max value
			std::cout << min << " < " << name << " < " << max << "    " << counter << std::endl;
		}
	}



// * ============================== * //
// * ------- STATIC MEMBERS ------- * //
// * ============================== * //

	std::list<CutObject*> CutObject::instances;

	/**
	 * @brief Print a table of cut names and their min/max and counter values.
	 */
	void CutObject::PrintAll()
	{
		/// -# Check if any instances of `CutObject` have been loaded.
		if(!CutObject::instances.size()) {
			std::cout << std::endl << "WARNING: no cuts defined" << std::endl << std::endl;
			return;
		}
		/// -# Print header of the table.
		std::cout << std::endl << "  "
			<< std::setw(12) << std::left  << "CUT NAME" << " | "
			<< std::setw(10) << std::right << "MIN" << " | "
			<< std::setw(10) << std::right << "MAX" << " | "
			<< std::setw(10) << std::right << "COUNT"
			<< std::endl;
		/// -# Print one row for each cut using `CutObject::Print`.
		std::list<CutObject*>::iterator cut = CutObject::instances.begin();
		for(; cut != CutObject::instances.end(); ++cut) {
			(*cut)->Print(12, 10, 10, 10);
		}
		/// -# Skip one line.
		std::cout << std::endl;
	}
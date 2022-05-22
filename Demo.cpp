/**
 * Demo file for the exercise on iterators
 *
 * @author Renana Rimon
 * @since 2022-05
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
using namespace std;

#include "OrgChart.hpp"
using namespace ariel;

int main() {
  OrgChart organization;
  cout << "-----------START DEMO-------------\n" << endl;

  organization.add_root("KING")
      .add_sub("KING", "PRINCE_1")         // Now the CTO is subordinate to the CEO
      .add_sub("KING", "PRINCESS")         // Now the CFO is subordinate to the CEO
      .add_sub("KING", "PRINCE_2")         // Now the COO is subordinate to the CEO
      .add_sub("PRINCE_1", "GIRL") // Now the VP Software is subordinate to the CTO
      .add_sub("PRINCESS", "BOY");      // Now the VP_BI is subordinate to the COO

  cout << organization << endl; /* Prints the org chart in a reasonable format. For example:
       KING
       |------------|---------|
       PRINCE_1  PRINCESS  PRINCE_2
       |            |
       GIRL        BOY
 */
  cout << "\n-----------LEVEL ORDER-------------\n" << endl;
  for (auto it = organization.begin_level_order(); it != organization.end_level_order(); ++it)
  {
    cout << (*it) << " " ;
  } // prints: KING PRINCE_1 PRINCESS PRINCE_2 GIRL BOY

  cout << "\n\n-----------REVERSE ORDER-------------\n" << endl;
  for (auto it = organization.begin_reverse_order(); it != organization.reverse_order(); ++it)
  {
    cout << (*it) << " " ;
  } // prints: GIRL BOY PRINCE_1 PRINCESS PRINCE_2 KING

  cout << "\n\n-----------PRE_ORDER-------------\n" << endl;
  for (auto it=organization.begin_preorder(); it!=organization.end_preorder(); ++it) {
    cout << (*it) << " " ;
  }  // prints: KING PRINCE_1 GIRL PRINCESS BOY PRINCE_2

  cout << "\n\n-----------FOR EACH - LEVEL ORDER-------------\n" << endl;
  for (auto element : organization)
  { // this should work like level order
    cout << element << " " ;
  } // prints: KING PRINCE_1 PRINCESS PRINCE_2 GIRL BOY

  cout << "\n\n-----------it->size()-------------\n" << endl;
  // demonstrate the arrow operator:
  for (auto it = organization.begin_level_order(); it != organization.end_level_order(); ++it)
  {
    cout << it->size() << " " ;
  } // prints: 4 8 8 8 4 3
  
  cout << "\n\n-----------THE END-------------\n" << endl;

  
}

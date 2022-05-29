#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <vector>

//descriptions for bottom functions & variables assume understanding of the top functions & variables
//r1 is the remaining slots for row 1, r2 is the remaining slots for row 2, & r3 is the remaining slots for r3.
//The general layout of tables is [up to 11 by 11 by 11 of remaining slots] [up to (11-r1) by (11-r2) by (11-r3) of successes)] [up to (r1+1) by (r2+1) by (r3+1) of probabilities].
//When I say 1st index, 2nd index, etc., I mean [1st index][2nd index][etc.] from the array format.
//The 25 to 75 at the end of the variables correspond to the probability of success.
//p25 to p75 represent the probability tables.
//d25 to d75 represent decision tables where 0 means choose row 1, 1 means choose row 2, 2 means choose row 3, & 3 means choose either row 1 or row 2.
//d25 to d75 don't need to keep track of row 3 successes since they have no effect on the decisions.
//e25 to e75 represent expected values of row 1 & row 2 where the final input [0] is for row 1 & [1] is for row 2.
//row 1 is assumed to be chosen in a tie, & the expected value of row 2 can be higher than the actual value because it is allowed to be chosen in a tie for optimization purposes.
//When selecting to choose row 2 in a tie in the calculator, row 1 is still selected but it swaps places with row 2 in the visual representation.

//Initializes all tables (about 3.5 GB of RAM used from all sources) & only needs to be done once.
void initTables(size_t r3, size_t r1, std::vector<std::vector<int>>& d25, std::vector<std::vector<int>>& d35, std::vector<std::vector<int>>& d45, std::vector<std::vector<int>>& d55, std::vector<std::vector<int>>& d65, std::vector<std::vector<int>>& d75, std::vector<std::vector<std::vector<long double>>>& e25, std::vector<std::vector<std::vector<long double>>>& e35, std::vector<std::vector<std::vector<long double>>>& e45, std::vector<std::vector<std::vector<long double>>>& e55, std::vector<std::vector<std::vector<long double>>>& e65, std::vector<std::vector<std::vector<long double>>>& e75, std::vector<std::vector<std::vector<long double>>>& p25, std::vector<std::vector<std::vector<long double>>>& p35, std::vector<std::vector<std::vector<long double>>>& p45, std::vector<std::vector<std::vector<long double>>>& p55, std::vector<std::vector<std::vector<long double>>>& p65, std::vector<std::vector<std::vector<long double>>>& p75);

//Initializes all tables except the probability tables (less than 70 MB of RAM used from all sources) & only needs to be done once.
void initTables2(size_t r3, size_t r1, std::vector<std::vector<int>>& d25, std::vector<std::vector<int>>& d35, std::vector<std::vector<int>>& d45, std::vector<std::vector<int>>& d55, std::vector<std::vector<int>>& d65, std::vector<std::vector<int>>& d75, std::vector<std::vector<std::vector<long double>>>& e25, std::vector<std::vector<std::vector<long double>>>& e35, std::vector<std::vector<std::vector<long double>>>& e45, std::vector<std::vector<std::vector<long double>>>& e55, std::vector<std::vector<std::vector<long double>>>& e65, std::vector<std::vector<std::vector<long double>>>& e75);

//base_d is the base decision table (6 probabilities by 20 columns by 10 rows) that minimizes successes in row 3 (10 rows), which maximizes successes in row 1 + row 2 (20 columns).
//Row 1 or row 2 is chosen with base_d is true and row 3 is chosen when base_d is false.
//These decisions are prioritized before deciding between row 1 & row 2.
//base_e is the base table for the expected values of row 1 + row 2 (6 probabilities by 21 columns by 11 rows). The extra column & row are used to represent 0 remaining slots.
//func1 is used to fill in the rest of the tables starting at (1, 1) after all of row 0 & all of column 0 have already been filled.
//i & j are the 1st 2 indecies of the tables. p1, p2, & p3 are used for last index, which pick the probability used for the table.
void func1(size_t i, size_t j, long double p, bool base_d[6][200], long double base_e[6][231], size_t p1, size_t p2, size_t p3);
void calcBaseTable(long double base_e[6][231], bool base_d[6][200]);

//The next 4 functions are used together & require calcBaseTable to be run to fill out the base decision tables, which will be prioritized before deciding between row 1 & row 2.
//slots is 1 + the amount of slots per row. The +1 comes from including slots = 0.
//dt stores d25 to d75 where the 1st index corresponds to the probability used & exp stores e25 to e75 where the 1st index corresponds to the probability used.
//r1s is the successes in row 1, r2s is the successes in row 2, r3s is the successes in row 3, & p is the probability of success.
//Coordinates are in the format (r1, r2, r3).
//func2 fills out the row 1 by row 3 plane starting at (1, 0, 1) after filling out all of row 0, all of column 0, & all of depth 0.
void func2(size_t slots, size_t r3, size_t r1, size_t r1s, size_t r2s, long double p, bool base_d[6][200], std::vector<std::vector<std::vector<int>>>& dt, std::vector<std::vector<std::vector<std::vector<long double>>>>& exp, size_t p1, size_t p2, size_t p3);

//func3 fills out the row 2 by row 3 plane starting at (0, 1, 1) after filling out all of row 0, all of column 0, & all of depth 0.
void func3(size_t slots, size_t r3, size_t r2, size_t r1s, size_t r2s, long double p, bool base_d[6][200], std::vector<std::vector<std::vector<int>>>& dt, std::vector<std::vector<std::vector<std::vector<long double>>>>& exp, size_t p1, size_t p2, size_t p3);

//w1 is the weight of row 1 where 0 <= w1 <= 1 & the weight of row 2 is 1 - w1. For example, w1 = 1 means row 1 is maximized & row 2 is minimized since its weight is 0.
//func4 is used to fill in the rest of the tables starting at (1, 1, 0) after filling out the row 1 by row 3 plane & row 2 by row 3 plane.
void func4(size_t slots, size_t r3, size_t r1, size_t r2, size_t r1s, size_t r2s, long double p, long double w1, bool base_d[6][200], std::vector<std::vector<std::vector<int>>>& dt, std::vector<std::vector<std::vector<std::vector<long double>>>>& exp, size_t p1, size_t p2, size_t p3);

//Dynamically fills tables based on the slots per row & weight of row 1, which is used to decide between row 1 & row 2 after prioritizing the base decision table.
void calcTable(size_t slots, bool base_d[6][200], long double w1, std::vector<std::vector<std::vector<int>>>& dt, std::vector<std::vector<std::vector<std::vector<long double>>>>& exp);

//coord is the index of the probability for outgoing translation, & variables ending with x represent parameters of the probability for incoming translation.
//Corresponding variables not ending with x represent parameters of the probability for outgoing translation.
//prob_t stores p25 to p75, & prob_i is the index for the probability of success. For example, prob_t[0] stores p25 & prob_t[5] stores p75.
//Returned is the probability represented by the parameters for incoming translation.
long double find_prob(size_t i, size_t j, size_t coord, size_t r1, size_t r2, size_t r3, size_t r1s, size_t r2s, size_t r3s, size_t r1x, size_t r2x, size_t r3x, size_t r1sx, size_t r2sx, size_t r3sx, std::vector<std::vector<std::vector<std::vector<long double>>>>& prob_t, size_t prob_i);

//Same as the above function, but skips the step of translating r1, r2, r3, r1s, r2s, & r3s to r1p, r2p, & r3p in cases where their translation can be easily determined manually.
//r1p, r2p, & r3p represent the amount of successes in each row for the probability calculation.
long double find_prob(size_t i, size_t j, size_t r1p, size_t r2p, size_t r3p, size_t r1x, size_t r2x, size_t r3x, size_t r1sx, size_t r2sx, size_t r3sx, std::vector<std::vector<std::vector<std::vector<long double>>>>& prob_t, size_t prob_i);

//Same as func2, but the probability tables are filled out instead of decision tables & expected value tables.
void func5(size_t slots, size_t r3, size_t r1, size_t r3s, size_t r1s, size_t r2s, long double p, bool base_d[6][200], std::vector<std::vector<std::vector<std::vector<long double>>>>& prob_t, size_t p1, size_t p2, size_t p3);

//Same as func3, but the probability tables are filled out instead of decision tables & expected value tables.
void func6(size_t slots, size_t r3, size_t r2, size_t r3s, size_t r1s, size_t r2s, long double p, bool base_d[6][200], std::vector<std::vector<std::vector<std::vector<long double>>>>& prob_t, size_t p1, size_t p2, size_t p3);

//Same as func4, but the probability tables are filled out instead of decision tables & expected value tables. The decision tables are used to guide this process.
void func7(size_t slots, size_t r3, size_t r1, size_t r2, size_t r1s, size_t r2s, size_t r3s, long double p, std::vector<std::vector<std::vector<int>>>& dt, std::vector<std::vector<std::vector<std::vector<long double>>>>& prob_t, size_t p1, size_t p2, size_t p3);

//Fills out the probability tables up to func5 & func6 in preparation for the next function calcProbabilities, which uses func7.
//This is similar to calcTable but the probability tables are filled out instead of decision tables & expected value tables.
//The reason for not combining this function with the next function is because a progress bar will only be used with the next function.
void initcalcProbabilities(size_t slots, bool base_d[6][200], std::vector<std::vector<std::vector<std::vector<long double>>>>& prob_t);

//Requires calcTable to be run (which requires calcBaseTable to be run) so the decision tables are filled out, which will guide the process of filling out the probability tables.
//Also, requires initcalcProbabilities to be run to meet the prerequisites for func7.
//Fills out the remaining probabilities in the probability table & is used for a progress bar.
void calcProbabilities(size_t r3, size_t r1, size_t slots, std::vector<std::vector<std::vector<int>>>& dt, std::vector<std::vector<std::vector<std::vector<long double>>>>& prob_t);

//The next 6 functions are used together. Their purpose is to fill out the tables based on weights & conditions placed on row 1 & row 2.
//This is similar to calcTable & calcProbabilities, but it is a different calculation because of the extra conditions placed on row 1 & row 2.
//r1c & r2c are the conditions on row 1 & row 2 where row 1 >= r1c & row 2 >= r2c
//func8 is like a combination of func4 & func7. Before it is run, func2, func3, func5, & func6 are run & decision table associated with func8 is initialized to -1.
//This is done to indicate if the decision table has already been set since it doesn't include r3s, but the probability table does include r3s, & all combinations with r3s are in the loop.
//func8 is called when the decision is independent of maximizing the probability of meeting the conditions placed on row 1 & row 2.
void func8(size_t r1c, size_t r2c, size_t slots, size_t r3, size_t r1, size_t r2, size_t r1s, size_t r2s, size_t r3s, long double p, long double w1, std::vector<std::vector<std::vector<int>>>& dt, std::vector<std::vector<std::vector<std::vector<long double>>>>& exp, std::vector<std::vector<std::vector<std::vector<long double>>>>& prob_t, size_t p1, size_t p2, size_t p3);

//Similar to find_prob but only need to translate the parameters to r1p, r2p, & r3p, then apply conditions r1c & r2c. If conditions are not met, then return 0.
//Otherwise, return the probability that meets the conditions.
long double applyconditions(size_t r1c, size_t r2c, size_t i, size_t j, size_t coord, size_t r1, size_t r2, size_t r3, size_t r1s, size_t r2s, size_t r3s, std::vector<std::vector<std::vector<std::vector<long double>>>>& prob_t, size_t prob_i);

//Calculates the probabilities of meeting the conditions on row 1 & row 2, then chooses the decision with the higher probability. If the probabilities are the same, then call func8.
void func9(size_t r1c, size_t r2c, size_t slots, size_t r3, size_t r1, size_t r2, size_t r1s, size_t r2s, size_t r3s, long double p, long double w1, std::vector<std::vector<std::vector<int>>>& dt, std::vector<std::vector<std::vector<std::vector<long double>>>>& exp, std::vector<std::vector<std::vector<std::vector<long double>>>>& prob_t, size_t p1, size_t p2, size_t p3);

//Prioritizes the base decision table, & can determine if the conditions on row 1 & row 2 cannot be met or are already met.
//If conditions cannot be met, then adjust the one(s) that cannot be met to the maximum value(s) that can be met.
void func10(size_t r1c, size_t r2c, size_t slots, size_t r3, size_t r1, size_t r2, size_t r1s, size_t r2s, size_t r3s, long double p, long double w1, bool base_d[6][200], std::vector<std::vector<std::vector<int>>>& dt, std::vector<std::vector<std::vector<std::vector<long double>>>>& exp, std::vector<std::vector<std::vector<std::vector<long double>>>>& prob_t, size_t p1, size_t p2, size_t p3);

//Similar to initcalcProbabilities but simultaneously does calculations from calcTable.
void initcalcTable2(size_t slots, bool base_d[6][200], std::vector<std::vector<std::vector<int>>>& dt, std::vector<std::vector<std::vector<std::vector<long double>>>>& exp, std::vector<std::vector<std::vector<std::vector<long double>>>>& prob_t);

//Similar to calcProbabilities but with conditions on row 1 & row 2 & simultaneously does calculations from calcTable.
void calcTable2(size_t r3, size_t r1, size_t r1c, size_t r2c, size_t slots, bool base_d[6][200], long double w1, std::vector<std::vector<std::vector<int>>>& dt, std::vector<std::vector<std::vector<std::vector<long double>>>>& exp, std::vector<std::vector<std::vector<std::vector<long double>>>>& prob_t);

long double applyconditions2(size_t r1c, size_t r2c, size_t r3c, size_t i, size_t j, size_t coord, size_t r1, size_t r2, size_t r3, size_t r1s, size_t r2s, size_t r3s, std::vector<std::vector<std::vector<std::vector<long double>>>>& prob_t, size_t prob_i);

void func14(size_t r1c, size_t r2c, size_t r3c, size_t slots, size_t r3, size_t r1, size_t r2, size_t r1s, size_t r2s, size_t r3s, long double p, long double w1, bool base_d[6][200], std::vector<std::vector<std::vector<int>>>& dt, std::vector<std::vector<std::vector<std::vector<long double>>>>& exp, std::vector<std::vector<std::vector<std::vector<long double>>>>& prob_t, size_t p1, size_t p2, size_t p3);

void func15(size_t r1c, size_t r2c, size_t r3c, size_t slots, size_t r3, size_t r1, size_t r2, size_t r1s, size_t r2s, size_t r3s, long double p, long double w1, bool base_d[6][200], std::vector<std::vector<std::vector<int>>>& dt, std::vector<std::vector<std::vector<std::vector<long double>>>>& exp, std::vector<std::vector<std::vector<std::vector<long double>>>>& prob_t, size_t p1, size_t p2, size_t p3);

void calcTable3(size_t r3, size_t r1, size_t r1c, size_t r2c, size_t r3c, size_t slots, bool base_d[6][200], long double w1, std::vector<std::vector<std::vector<int>>>& dt, std::vector<std::vector<std::vector<std::vector<long double>>>>& exp, std::vector<std::vector<std::vector<std::vector<long double>>>>& prob_t);

long double finde2(size_t i, size_t j, size_t coord, size_t r1, size_t r2, size_t r3, size_t r1s, size_t r2s, size_t r3s, std::vector<std::vector<std::vector<std::vector<long double>>>>& prob_t, size_t prob_i);

long double expr3(size_t i, size_t j, size_t r1, size_t r2, size_t r3, size_t r1s, size_t r2s, size_t r3s, std::vector<std::vector<std::vector<std::vector<long double>>>>& prob_t, size_t prob_i);

//Finds the expected value of row 2 by converting the parameters to r1p, r2p, & r3p to find the probability then return its product with r2p
//The expected value in exp assumes row 2 can be chosen in a tie for optimization purposes, but it will not be chosen for the calculations, so this function will find the actual value.
long double finde(size_t i, size_t j, size_t coord, size_t r1, size_t r2, size_t r3, size_t r1s, size_t r2s, size_t r3s, std::vector<std::vector<std::vector<std::vector<long double>>>>& prob_t, size_t prob_i);

//Sums up the individual expected values to find the total expected value for row 2
long double expr2(size_t i, size_t j, size_t r1, size_t r2, size_t r3, size_t r1s, size_t r2s, size_t r3s, std::vector<std::vector<std::vector<std::vector<long double>>>>& prob_t, size_t prob_i);

//Finds an individual probability associated with P(row 1 + row 2 >= r12p and row 3 <= r4p)
long double findp1(size_t r12p, size_t r4p, size_t i, size_t j, size_t coord, size_t r1, size_t r2, size_t r3, size_t r1s, size_t r2s, size_t r3s, std::vector<std::vector<std::vector<std::vector<long double>>>>& prob_t, size_t prob_i);

//Finds the probability P(row 1 + row 2 >= r12p and row 3 <= r4p) by totaling the individual probabilities
void func11(size_t r12p, size_t r4p, long double& prob2, size_t i, size_t j, size_t r1, size_t r2, size_t r3, size_t r1s, size_t r2s, size_t r3s, std::vector<std::vector<std::vector<std::vector<long double>>>>& prob_t, int prob_i);

//Finds an individual probability associated with P(row 1 >= r1pc and row 2 >= r2pc and row 3 <= r3pc)
long double findp2(size_t r3pc, size_t r1pc, size_t r2pc, size_t i, size_t j, size_t coord, size_t r1, size_t r2, size_t r3, size_t r1s, size_t r2s, size_t r3s, std::vector<std::vector<std::vector<std::vector<long double>>>>& prob_t, size_t prob_i);

//Finds the probability P(row 1 >= r1pc and row 2 >= r2pc and row 3 <= r3pc) by totaling the individual probabilities
void func12(size_t r3pc, size_t r1pc, size_t r2pc, long double& prob, size_t i, size_t j, size_t r1, size_t r2, size_t r3, size_t r1s, size_t r2s, size_t r3s, std::vector<std::vector<std::vector<std::vector<long double>>>>& prob_t, int prob_i);

//Combines func11 & func12
void update_probabilities(long double& prob, long double& prob2, int p, size_t smax, size_t r1p, size_t r2p, size_t r3p, size_t r12p, size_t r4p, size_t s1, size_t r1s, size_t r2s, size_t r3s, size_t row1, size_t row2, size_t row3, std::vector<std::vector<std::vector<std::vector<long double>>>>& prob_t);

//Updates the optimal decision (choice), expected value of row 1, expected value of row 2, & expected value of row 3 based on the changes to the other parameters
//s1 is the current amount of slots per row, smax is the applied amount of slots per row, & row1/row2/row3 is the total amount of slots succeeded & failed in the corresponding row.
void func13(size_t smax, int& choice, size_t s1, size_t row3, size_t r1s, size_t r2s, size_t r3s, size_t row1, size_t row2, long double& r1e, long double& r2e, long double& r3e, bool p_m, bool sacrifice, long double base_e[6][231], std::vector<std::vector<std::vector<int>>>& dt, std::vector<std::vector<std::vector<std::vector<long double>>>>& exp, std::vector<std::vector<std::vector<std::vector<long double>>>>& prob_t, int prob_i);

//Combines func13 & update_probabilities
void update_changes(long double& prob, long double& prob2, size_t r1p, size_t r2p, size_t r3p, size_t r12p, size_t r4p, size_t smax, int& p, int& choice, size_t s1, size_t& row3, size_t& r1s, size_t& r2s, size_t& r3s, size_t& row1, size_t& row2, long double& r1e, long double& r2e, long double& r3e, bool p_m, bool sacrifice, long double base_e[6][231], std::vector<std::vector<std::vector<int>>>& dt, std::vector<std::vector<std::vector<std::vector<long double>>>>& exp, std::vector<std::vector<std::vector<std::vector<long double>>>>& prob_t);

#endif 
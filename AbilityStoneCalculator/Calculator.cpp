#include "Calculator.h"

//See header file for general descriptions of each function and variable

//The tables allow for a change of slots without needing to recalculate. Changing the slots will change the dimensions for parts of the tables.
//Therefore, the maximum size of the dimensions must be determined to prevent recalculation.
void initTables(size_t r3, size_t r1, std::vector<std::vector<int>>& d25, std::vector<std::vector<int>>& d35, std::vector<std::vector<int>>& d45, std::vector<std::vector<int>>& d55, std::vector<std::vector<int>>& d65, std::vector<std::vector<int>>& d75, std::vector<std::vector<std::vector<long double>>>& e25, std::vector<std::vector<std::vector<long double>>>& e35, std::vector<std::vector<std::vector<long double>>>& e45, std::vector<std::vector<std::vector<long double>>>& e55, std::vector<std::vector<std::vector<long double>>>& e65, std::vector<std::vector<std::vector<long double>>>& e75, std::vector<std::vector<std::vector<long double>>>& p25, std::vector<std::vector<std::vector<long double>>>& p35, std::vector<std::vector<std::vector<long double>>>& p45, std::vector<std::vector<std::vector<long double>>>& p55, std::vector<std::vector<std::vector<long double>>>& p65, std::vector<std::vector<std::vector<long double>>>& p75) {
	size_t a = 0, b = 0, c = 0, m = 0, m2 = 0, t = 0, m3 = 0, n = 0;
	for (size_t r2 = 0; r2 < 11; r2++) {
		m = (11 - r2) * (11 - r1) * (11 - r3); //dimensions of success parameters for probability table at slots = 11
		m2 = (11 - r2) * (11 - r1); //dimensions of success parameters for decision table and expected value table at slots = 11
		m3 = (r2 + 1) * (r1 + 1) * (r3 + 1); //dimensions of the parameters for probabilities at slots = 11
		n = 121 * r3 + 11 * r1 + r2; //index based on the available amount of slots in each row at slots = 11
		for (size_t slots = 10; slots > 1; slots--) { //finds the dimensions for all other slots values to determine the maximum size needed
			a = n / (slots * slots);
			if (a >= slots)
				continue;
			b = (n - slots * slots * a) / slots;
			c = n - slots * slots * a - slots * b;
			t = (slots - a) * (slots - b) * (slots - c);
			if (t > m)
				m = t;
			t = (slots - b) * (slots - c);
			if (t > m2)
				m2 = t;
			t = (a + 1) * (b + 1) * (c + 1);
			if (t > m3)
				m3 = t;
		}
		std::vector<int>d1(m2, 0);
		std::vector<int>d2(m2, 0);
		std::vector<int>d3(m2, 0);
		std::vector<int>d4(m2, 0);
		std::vector<int>d5(m2, 0);
		std::vector<int>d6(m2, 0);
		std::vector<std::vector<long double>> e1(m2, std::vector<long double>(2, 0));
		std::vector<std::vector<long double>> e2(m2, std::vector<long double>(2, 0));
		std::vector<std::vector<long double>> e3(m2, std::vector<long double>(2, 0));
		std::vector<std::vector<long double>> e4(m2, std::vector<long double>(2, 0));
		std::vector<std::vector<long double>> e5(m2, std::vector<long double>(2, 0));
		std::vector<std::vector<long double>> e6(m2, std::vector<long double>(2, 0));
		d25.push_back(d1);
		d35.push_back(d2);
		d45.push_back(d3);
		d55.push_back(d4);
		d65.push_back(d5);
		d75.push_back(d6);
		e25.push_back(e1);
		e35.push_back(e2);
		e45.push_back(e3);
		e55.push_back(e4);
		e65.push_back(e5);
		e75.push_back(e6);
		std::vector<std::vector<long double>> p1(m, std::vector<long double>(m3, 0));
		std::vector<std::vector<long double>> p2(m, std::vector<long double>(m3, 0));
		std::vector<std::vector<long double>> p3(m, std::vector<long double>(m3, 0));
		std::vector<std::vector<long double>> p4(m, std::vector<long double>(m3, 0));
		std::vector<std::vector<long double>> p5(m, std::vector<long double>(m3, 0));
		std::vector<std::vector<long double>> p6(m, std::vector<long double>(m3, 0));
		p25.push_back(p1);
		p35.push_back(p2);
		p45.push_back(p3);
		p55.push_back(p4);
		p65.push_back(p5);
		p75.push_back(p6);
	}
}

void initTables2(size_t r3, size_t r1, std::vector<std::vector<int>>& d25, std::vector<std::vector<int>>& d35, std::vector<std::vector<int>>& d45, std::vector<std::vector<int>>& d55, std::vector<std::vector<int>>& d65, std::vector<std::vector<int>>& d75, std::vector<std::vector<std::vector<long double>>>& e25, std::vector<std::vector<std::vector<long double>>>& e35, std::vector<std::vector<std::vector<long double>>>& e45, std::vector<std::vector<std::vector<long double>>>& e55, std::vector<std::vector<std::vector<long double>>>& e65, std::vector<std::vector<std::vector<long double>>>& e75) {
	size_t a = 0, b = 0, c = 0, m = 0, t = 0, n = 0;
	for (size_t r2 = 0; r2 < 11; r2++) {
		m = (11 - r2) * (11 - r1);
		n = 121 * r3 + 11 * r1 + r2;
		for (size_t slots = 10; slots > 1; slots--) {
			a = n / (slots * slots);
			if (a >= slots)
				continue;
			b = (n - slots * slots * a) / slots;
			c = n - slots * slots * a - slots * b;
			t = (slots - b) * (slots - c);
			if (t > m)
				m = t;
		}
		std::vector<int>d1(m, 0);
		std::vector<int>d2(m, 0);
		std::vector<int>d3(m, 0);
		std::vector<int>d4(m, 0);
		std::vector<int>d5(m, 0);
		std::vector<int>d6(m, 0);
		std::vector<std::vector<long double>> e1(m, std::vector<long double>(2, 0));
		std::vector<std::vector<long double>> e2(m, std::vector<long double>(2, 0));
		std::vector<std::vector<long double>> e3(m, std::vector<long double>(2, 0));
		std::vector<std::vector<long double>> e4(m, std::vector<long double>(2, 0));
		std::vector<std::vector<long double>> e5(m, std::vector<long double>(2, 0));
		std::vector<std::vector<long double>> e6(m, std::vector<long double>(2, 0));
		d25.push_back(d1);
		d35.push_back(d2);
		d45.push_back(d3);
		d55.push_back(d4);
		d65.push_back(d5);
		d75.push_back(d6);
		e25.push_back(e1);
		e35.push_back(e2);
		e45.push_back(e3);
		e55.push_back(e4);
		e65.push_back(e5);
		e75.push_back(e6);
	}
}

void func1(size_t i, size_t j, long double p, bool base_d[6][200], long double base_e[6][231], size_t p1, size_t p2, size_t p3) {
	long double rg = p * base_e[p2][21 * i + j - 1] + (1 - p) * base_e[p3][21 * i + j - 1]; //expected value of row 3 for choosing row 1 or row 2
	long double rb = p + p * base_e[p2][21 * (i - 1) + j] + (1 - p) * base_e[p3][21 * (i - 1) + j]; //expected value of row 3 for choosing row 3
	if (rg < rb) { //choose the decision that minimizes the expected value of row 3
		base_d[p1][20 * (i - 1) + j - 1] = true; //means row 1 or row 2 is chosen
		base_e[p1][21 * i + j] = rg;
	}
	else {
		base_d[p1][20 * (i - 1) + j - 1] = false; //means row 3 is chosen
		base_e[p1][21 * i + j] = rb;
	}
}

void calcBaseTable(long double base_e[6][231], bool base_d[6][200]) {
	for (size_t i = 0; i < 21; i++)
		for (size_t prob_i = 0; prob_i < 6; prob_i++)
			base_e[prob_i][i] = 0;
	for (size_t prob_i = 0; prob_i < 6; prob_i++)
		base_e[prob_i][21] = 0.25 + 0.1 * prob_i;
	for (size_t i = 2; i < 11; i++)
		for (size_t prob_i = 0; prob_i < 6; prob_i++)
			base_e[prob_i][21 * i] = 0.25 + 0.1 * prob_i + (0.25 + 0.1 * prob_i) * base_e[prob_i > 0 ? prob_i - 1 : 0][21 * (i - 1)] + (0.75 - 0.1 * prob_i) * base_e[prob_i < 5 ? prob_i + 1 : 5][21 * (i - 1)];
	for (size_t i = 1; i < 11; i++)
		for (size_t j = 1; j < 21; j++)
			for (size_t prob_i = 0; prob_i < 6; prob_i++)
				func1(i, j, 0.25 + 0.1 * prob_i, base_d, base_e, prob_i, prob_i > 0 ? prob_i - 1 : 0, prob_i < 5 ? prob_i + 1 : 5);
}

void func2(size_t slots, size_t r3, size_t r1, size_t r1s, size_t r2s, long double p, bool base_d[6][200], std::vector<std::vector<std::vector<int>>>& dt, std::vector<std::vector<std::vector<std::vector<long double>>>>& exp, size_t p1, size_t p2, size_t p3) {
	exp[p1][slots * slots * r3 + slots * r1][slots * r1s + r2s][1] = 0;
	if (base_d[p1][20 * (r3 - 1) + r1 - 1]) { //choose row 1
		dt[p1][slots * slots * r3 + slots * r1][slots * r1s + r2s] = 0;
		exp[p1][slots * slots * r3 + slots * r1][slots * r1s + r2s][0] = p + p * exp[p2][slots * slots * r3 + slots * (r1 - 1)][slots * (r1s + 1) + r2s][0] + (1 - p) * exp[p3][slots * slots * r3 + slots * (r1 - 1)][slots * r1s + r2s][0];
	}
	else {  //choose row 3
		dt[p1][slots * slots * r3 + slots * r1][slots * r1s + r2s] = 2;
		exp[p1][slots * slots * r3 + slots * r1][slots * r1s + r2s][0] = p * exp[p2][slots * slots * (r3 - 1) + slots * r1][slots * r1s + r2s][0] + (1 - p) * exp[p3][slots * slots * (r3 - 1) + slots * r1][slots * r1s + r2s][0];
	}
}

void func3(size_t slots, size_t r3, size_t r2, size_t r1s, size_t r2s, long double p, bool base_d[6][200], std::vector<std::vector<std::vector<int>>>& dt, std::vector<std::vector<std::vector<std::vector<long double>>>>& exp, size_t p1, size_t p2, size_t p3) {
	exp[p1][slots * slots * r3 + r2][(slots - r2) * r1s + r2s][0] = 0;
	if (base_d[p1][20 * (r3 - 1) + r2 - 1]) { //choose row 2
		dt[p1][slots * slots * r3 + r2][(slots - r2) * r1s + r2s] = 1;
		exp[p1][slots * slots * r3 + r2][(slots - r2) * r1s + r2s][1] = p + p * exp[p2][slots * slots * r3 + r2 - 1][(slots + 1 - r2) * r1s + r2s + 1][1] + (1 - p) * exp[p3][slots * slots * r3 + r2 - 1][(slots + 1 - r2) * r1s + r2s][1];
	}
	else {  //choose row 3
		dt[p1][slots * slots * r3 + r2][(slots - r2) * r1s + r2s] = 2;
		exp[p1][slots * slots * r3 + r2][(slots - r2) * r1s + r2s][1] = p * exp[p2][slots * slots * (r3 - 1) + r2][(slots - r2) * r1s + r2s][1] + (1 - p) * exp[p3][slots * slots * (r3 - 1) + r2][(slots - r2) * r1s + r2s][1];
	}
}

void func4(size_t slots, size_t r3, size_t r1, size_t r2, size_t r1s, size_t r2s, long double p, long double w1, bool base_d[6][200], std::vector<std::vector<std::vector<int>>>& dt, std::vector<std::vector<std::vector<std::vector<long double>>>>& exp, size_t p1, size_t p2, size_t p3) {
	if (r3 == 0 || base_d[p1][20 * (r3 - 1) + r1 + r2 - 1]) { //choose row 1 or row 2
		//evaluate E(row 1) and E(row 2) when choosing row 1 then calculate absolute error from desired weight distribution
		long double a = p + p * exp[p2][slots * slots * r3 + slots * (r1 - 1) + r2][(slots - r2) * (r1s + 1) + r2s][0] + (1 - p) * exp[p3][slots * slots * r3 + slots * (r1 - 1) + r2][(slots - r2) * r1s + r2s][0];
		long double b = p * exp[p2][slots * slots * r3 + slots * (r1 - 1) + r2][(slots - r2) * (r1s + 1) + r2s][1] + (1 - p) * exp[p3][slots * slots * r3 + slots * (r1 - 1) + r2][(slots - r2) * r1s + r2s][1];
		long double r1error = abs(r1s + a - w1 * (r1s + a + r2s + b)) + abs(r2s + b - (1 - w1) * (r1s + a + r2s + b));
		//evaluate E(row 1) and E(row 2) when choosing row 2 then calculate absolute error from desired weight distribution
		long double c = p * exp[p2][slots * slots * r3 + slots * r1 + r2 - 1][(slots + 1 - r2) * r1s + r2s + 1][0] + (1 - p) * exp[p3][slots * slots * r3 + slots * r1 + r2 - 1][(slots + 1 - r2) * r1s + r2s][0];
		long double d = p + p * exp[p2][slots * slots * r3 + slots * r1 + r2 - 1][(slots + 1 - r2) * r1s + r2s + 1][1] + (1 - p) * exp[p3][slots * slots * r3 + slots * r1 + r2 - 1][(slots + 1 - r2) * r1s + r2s][1];
		long double r2error = abs(r1s + c - w1 * (r1s + c + r2s + d)) + abs(r2s + d - (1 - w1) * (r1s + c + r2s + d));
		if (r1error < r2error) {
			dt[p1][slots * slots * r3 + slots * r1 + r2][(slots - r2) * r1s + r2s] = 0;
			exp[p1][slots * slots * r3 + slots * r1 + r2][(slots - r2) * r1s + r2s][0] = a;
			exp[p1][slots * slots * r3 + slots * r1 + r2][(slots - r2) * r1s + r2s][1] = b;
		}
		else if (r1error > r2error) {
			dt[p1][slots * slots * r3 + slots * r1 + r2][(slots - r2) * r1s + r2s] = 1;
			exp[p1][slots * slots * r3 + slots * r1 + r2][(slots - r2) * r1s + r2s][0] = c;
			exp[p1][slots * slots * r3 + slots * r1 + r2][(slots - r2) * r1s + r2s][1] = d;
		}
		else {
			dt[p1][slots * slots * r3 + slots * r1 + r2][(slots - r2) * r1s + r2s] = 3;
			exp[p1][slots * slots * r3 + slots * r1 + r2][(slots - r2) * r1s + r2s][0] = a; //doesn't have a preference
			exp[p1][slots * slots * r3 + slots * r1 + r2][(slots - r2) * r1s + r2s][1] = d;
		}
	}
	else { //choose row 3
		dt[p1][slots * slots * r3 + slots * r1 + r2][(slots - r2) * r1s + r2s] = 2;
		exp[p1][slots * slots * r3 + slots * r1 + r2][(slots - r2) * r1s + r2s][0] = p * exp[p2][slots * slots * (r3 - 1) + slots * r1 + r2][(slots - r2) * r1s + r2s][0] + (1 - p) * exp[p3][slots * slots * (r3 - 1) + slots * r1 + r2][(slots - r2) * r1s + r2s][0];
		exp[p1][slots * slots * r3 + slots * r1 + r2][(slots - r2) * r1s + r2s][1] = p * exp[p2][slots * slots * (r3 - 1) + slots * r1 + r2][(slots - r2) * r1s + r2s][1] + (1 - p) * exp[p3][slots * slots * (r3 - 1) + slots * r1 + r2][(slots - r2) * r1s + r2s][1];
	}
}

void calcTable(size_t slots, bool base_d[6][200], long double w1, std::vector<std::vector<std::vector<int>>>& dt, std::vector<std::vector<std::vector<std::vector<long double>>>>& exp) {
	for (size_t r3 = 1; r3 < slots; r3++) //(0,0,r3)
		for (size_t r1s = 0; r1s < slots; r1s++)
			for (size_t r2s = 0; r2s < slots; r2s++)
				for (size_t prob_i = 0; prob_i < 6; prob_i++) {
					dt[prob_i][slots * slots * r3][slots * r1s + r2s] = 2;
					exp[prob_i][slots * slots * r3][slots * r1s + r2s][0] = 0;
					exp[prob_i][slots * slots * r3][slots * r1s + r2s][1] = 0;
				}
	for (size_t r1 = 1; r1 < slots; r1++) //(r1,0,0)
		for (size_t r1s = 0; r1s < slots - r1; r1s++)
			for (size_t r2s = 0; r2s < slots; r2s++)
				for (size_t prob_i = 0; prob_i < 6; prob_i++) {
					exp[prob_i][slots * r1][slots * r1s + r2s][0] = 0.25 + 0.1 * prob_i + (0.25 + 0.1 * prob_i) * exp[prob_i > 0 ? prob_i - 1 : 0][slots * (r1 - 1)][slots * (r1s + 1) + r2s][0] + (0.75 - 0.1 * prob_i) * exp[prob_i < 5 ? prob_i + 1 : 5][slots * (r1 - 1)][slots * r1s + r2s][0];
					exp[prob_i][slots * r1][slots * r1s + r2s][1] = 0;
					dt[prob_i][slots * r1][slots * r1s + r2s] = 0;
				}
	for (size_t r2 = 1; r2 < slots; r2++) //(0,r2,0)
		for (size_t r1s = 0; r1s < slots; r1s++)
			for (size_t r2s = 0; r2s < slots - r2; r2s++)
				for (size_t prob_i = 0; prob_i < 6; prob_i++) {
					exp[prob_i][r2][(slots - r2) * r1s + r2s][1] = 0.25 + 0.1 * prob_i + (0.25 + 0.1 * prob_i) * exp[prob_i > 0 ? prob_i - 1 : 0][r2 - 1][(slots + 1 - r2) * r1s + r2s + 1][1] + (0.75 - 0.1 * prob_i) * exp[prob_i < 5 ? prob_i + 1 : 5][r2 - 1][(slots + 1 - r2) * r1s + r2s][1];
					exp[prob_i][r2][(slots - r2) * r1s + r2s][0] = 0;
					dt[prob_i][r2][(slots - r2) * r1s + r2s] = 1;
				}
	for (size_t r3 = 1; r3 < slots; r3++) //(r1,0,r3)
		for (size_t r1 = 1; r1 < slots; r1++)
			for (size_t r1s = 0; r1s < slots - r1; r1s++)
				for (size_t r2s = 0; r2s < slots; r2s++)
					for (size_t prob_i = 0; prob_i < 6; prob_i++)
						func2(slots, r3, r1, r1s, r2s, 0.25 + 0.1 * prob_i, base_d, dt, exp, prob_i, prob_i > 0 ? prob_i - 1 : 0, prob_i < 5 ? prob_i + 1 : 5);
	for (size_t r3 = 1; r3 < slots; r3++) //(0,r2,r3)
		for (size_t r2 = 1; r2 < slots; r2++)
			for (size_t r1s = 0; r1s < slots; r1s++)
				for (size_t r2s = 0; r2s < slots - r2; r2s++)
					for (size_t prob_i = 0; prob_i < 6; prob_i++)
						func3(slots, r3, r2, r1s, r2s, 0.25 + 0.1 * prob_i, base_d, dt, exp, prob_i, prob_i > 0 ? prob_i - 1 : 0, prob_i < 5 ? prob_i + 1 : 5);
	for (size_t r3 = 0; r3 < slots; r3++) //(r1,r2,r3)
		for (size_t r1 = 1; r1 < slots; r1++)
			for (size_t r2 = 1; r2 < slots; r2++)
				for (size_t r1s = 0; r1s < slots - r1; r1s++)
					for (size_t r2s = 0; r2s < slots - r2; r2s++)
						for (size_t prob_i = 0; prob_i < 6; prob_i++)
							func4(slots, r3, r1, r2, r1s, r2s, 0.25 + 0.1 * prob_i, w1, base_d, dt, exp, prob_i, prob_i > 0 ? prob_i - 1 : 0, prob_i < 5 ? prob_i + 1 : 5);
}

//The format of the last index of prob_t is to follow a priority system: r2->r1->r3 for the column, r1->r3 for the row, & r3 for the depth.
long double find_prob(size_t i, size_t j, size_t coord, size_t r1, size_t r2, size_t r3, size_t r1s, size_t r2s, size_t r3s, size_t r1x, size_t r2x, size_t r3x, size_t r1sx, size_t r2sx, size_t r3sx, std::vector<std::vector<std::vector<std::vector<long double>>>>& prob_t, size_t prob_i) {
	size_t r1p = 0, r2p = 0, r3p = 0; //translate coord to r1p, r2p, r3p
	if (r1 == 0) {
		r1p = r1s;
		if (r2 == 0) {
			r2p = r2s;
			r3p = coord + r3s;
		}
		else if (r3 == 0) {
			r3p = r3s;
			r2p = coord + r2s;
		}
		else { //r2p is column, r3p is row
			r3p = r3s + coord / (r2 + 1);
			r2p = r2s + coord % (r2 + 1);
		}
	}
	else if (r2 == 0) {
		r2p = r2s;
		if (r3 == 0) {
			r3p = r3s;
			r1p = coord + r1s;
		}
		else { //r1p is column, r3p is row
			r3p = r3s + coord / (r1 + 1);
			r1p = r1s + coord % (r1 + 1);
		}
	}
	else if (r3 == 0) {
		r3p = r3s; //r2p is column, r1p is row
		r1p = r1s + coord / (r2 + 1);
		r2p = r2s + coord % (r2 + 1);
	}
	else { //r2p is column, r1p is row, r3p is depth
		size_t s = (r1 + 1) * (r2 + 1);
		size_t t = coord % s;
		r3p = r3s + coord / s;
		r1p = r1s + t / (r2 + 1);
		r2p = r2s + t % (r2 + 1);
	} //this is checking if 3 boundaries are intersected by 3 other boundaries
	if (r1sx + r1x < r1p || r2sx + r2x < r2p || r3sx + r3x < r3p || r1p < r1sx || r2p < r2sx || r3p < r3sx)
		return 0;
	if (r1x == 0) { //need to consider all the possible coordinate arrangements
		if (r2x == 0)
			return prob_t[prob_i][i][j][r3p - r3sx];
		else if (r3x == 0)
			return prob_t[prob_i][i][j][r2p - r2sx];
		else return prob_t[prob_i][i][j][(r2x + 1) * (r3p - r3sx) + r2p - r2sx];
	}
	else if (r2x == 0) {
		if (r3x == 0)
			return prob_t[prob_i][i][j][r1p - r1sx];
		else return prob_t[prob_i][i][j][(r1x + 1) * (r3p - r3sx) + r1p - r1sx];
	}
	else if (r3x == 0)
		return prob_t[prob_i][i][j][(r2x + 1) * (r1p - r1sx) + r2p - r2sx];
	else return prob_t[prob_i][i][j][(r1x + 1) * (r2x + 1) * (r3p - r3sx) + (r2x + 1) * (r1p - r1sx) + r2p - r2sx];
	return 0;
}

long double find_prob(size_t i, size_t j, size_t r1p, size_t r2p, size_t r3p, size_t r1x, size_t r2x, size_t r3x, size_t r1sx, size_t r2sx, size_t r3sx, std::vector<std::vector<std::vector<std::vector<long double>>>>& prob_t, size_t prob_i) {
	//this is checking if 3 boundaries are intersected by 3 other boundaries
	if (r1sx + r1x < r1p || r2sx + r2x < r2p || r3sx + r3x < r3p || r1p < r1sx || r2p < r2sx || r3p < r3sx)
		return 0;
	if (r1x == 0) { //need to consider all the possible coordinate arrangements
		if (r2x == 0)
			return prob_t[prob_i][i][j][r3p - r3sx];
		else if (r3x == 0)
			return prob_t[prob_i][i][j][r2p - r2sx];
		else return prob_t[prob_i][i][j][(r2x + 1) * (r3p - r3sx) + r2p - r2sx];
	}
	else if (r2x == 0) {
		if (r3x == 0)
			return prob_t[prob_i][i][j][r1p - r1sx];
		else return prob_t[prob_i][i][j][(r1x + 1) * (r3p - r3sx) + r1p - r1sx];
	}
	else if (r3x == 0)
		return prob_t[prob_i][i][j][(r2x + 1) * (r1p - r1sx) + r2p - r2sx];
	else return prob_t[prob_i][i][j][(r1x + 1) * (r2x + 1) * (r3p - r3sx) + (r2x + 1) * (r1p - r1sx) + r2p - r2sx];
	return 0;
}

void func5(size_t slots, size_t r3, size_t r1, size_t r3s, size_t r1s, size_t r2s, long double p, bool base_d[6][200], std::vector<std::vector<std::vector<std::vector<long double>>>>& prob_t, size_t p1, size_t p2, size_t p3) {
	size_t a = slots * slots * r3 + slots * r1, b = slots * (slots - r1) * r3s + slots * r1s + r2s;
	if (base_d[p1][20 * (r3 - 1) + r1 - 1]) { //choose row 1
		size_t d = slots * slots * r3 + slots * (r1 - 1), e = slots * (slots + 1 - r1) * r3s + slots * (r1s + 1) + r2s, f = slots * (slots + 1 - r1) * r3s + slots * r1s + r2s;
		for (size_t c = 0; c < (r3 + 1) * (r1 + 1); c++)
			prob_t[p1][a][b][c] = p * find_prob(d, e, c, r1, 0, r3, r1s, r2s, r3s, r1 - 1, 0, r3, r1s + 1, r2s, r3s, prob_t, p2) + (1 - p) * find_prob(d, f, c, r1, 0, r3, r1s, r2s, r3s, r1 - 1, 0, r3, r1s, r2s, r3s, prob_t, p3);
	}
	else {  //choose row 3
		size_t d = slots * slots * (r3 - 1) + slots * r1, e = slots * (slots - r1) * (r3s + 1) + slots * r1s + r2s;
		for (size_t c = 0; c < (r3 + 1) * (r1 + 1); c++)
			prob_t[p1][a][b][c] = p * find_prob(d, e, c, r1, 0, r3, r1s, r2s, r3s, r1, 0, r3 - 1, r1s, r2s, r3s + 1, prob_t, p2) + (1 - p) * find_prob(d, b, c, r1, 0, r3, r1s, r2s, r3s, r1, 0, r3 - 1, r1s, r2s, r3s, prob_t, p3);
	}
}

void func6(size_t slots, size_t r3, size_t r2, size_t r3s, size_t r1s, size_t r2s, long double p, bool base_d[6][200], std::vector<std::vector<std::vector<std::vector<long double>>>>& prob_t, size_t p1, size_t p2, size_t p3) {
	size_t a = slots * slots * r3 + r2, b = slots * (slots - r2) * r3s + (slots - r2) * r1s + r2s;
	if (base_d[p1][20 * (r3 - 1) + r2 - 1]) { //choose row 2
		size_t e = slots * (slots + 1 - r2) * r3s + (slots + 1 - r2) * r1s + r2s;
		for (size_t c = 0; c < (r3 + 1) * (r2 + 1); c++)
			prob_t[p1][a][b][c] = p * find_prob(a - 1, e + 1, c, 0, r2, r3, r1s, r2s, r3s, 0, r2 - 1, r3, r1s, r2s + 1, r3s, prob_t, p2) + (1 - p) * find_prob(a - 1, e, c, 0, r2, r3, r1s, r2s, r3s, 0, r2 - 1, r3, r1s, r2s, r3s, prob_t, p3);
	}
	else {  //choose row 3
		size_t d = slots * slots * (r3 - 1) + r2, e = slots * (slots - r2) * (r3s + 1) + (slots - r2) * r1s + r2s;
		for (size_t c = 0; c < (r3 + 1) * (r2 + 1); c++)
			prob_t[p1][a][b][c] = p * find_prob(d, e, c, 0, r2, r3, r1s, r2s, r3s, 0, r2, r3 - 1, r1s, r2s, r3s + 1, prob_t, p2) + (1 - p) * find_prob(d, b, c, 0, r2, r3, r1s, r2s, r3s, 0, r2, r3 - 1, r1s, r2s, r3s, prob_t, p3);
	}
}

void func7(size_t slots, size_t r3, size_t r1, size_t r2, size_t r1s, size_t r2s, size_t r3s, long double p, std::vector<std::vector<std::vector<int>>>& dt, std::vector<std::vector<std::vector<std::vector<long double>>>>& prob_t, size_t p1, size_t p2, size_t p3) {
	size_t a = slots * slots * r3 + slots * r1 + r2, b = (slots - r2) * (slots - r1) * r3s + (slots - r2) * r1s + r2s;
	if (dt[p1][a][(slots - r2) * r1s + r2s] == 2) {
		size_t d = slots * slots * (r3 - 1) + slots * r1 + r2, e = (slots - r2) * (slots - r1) * (r3s + 1) + (slots - r2) * r1s + r2s;
		for (size_t c = 0; c < (r3 + 1) * (r1 + 1) * (r2 + 1); c++)
			prob_t[p1][a][b][c] = p * find_prob(d, e, c, r1, r2, r3, r1s, r2s, r3s, r1, r2, r3 - 1, r1s, r2s, r3s + 1, prob_t, p2) + (1 - p) * find_prob(d, b, c, r1, r2, r3, r1s, r2s, r3s, r1, r2, r3 - 1, r1s, r2s, r3s, prob_t, p3);
	}
	else if (dt[p1][a][(slots - r2) * r1s + r2s] == 1) {
		size_t e = (slots + 1 - r2) * (slots - r1) * r3s + (slots + 1 - r2) * r1s + r2s;
		for (size_t c = 0; c < (r3 + 1) * (r1 + 1) * (r2 + 1); c++)
			prob_t[p1][a][b][c] = p * find_prob(a - 1, e + 1, c, r1, r2, r3, r1s, r2s, r3s, r1, r2 - 1, r3, r1s, r2s + 1, r3s, prob_t, p2) + (1 - p) * find_prob(a - 1, e, c, r1, r2, r3, r1s, r2s, r3s, r1, r2 - 1, r3, r1s, r2s, r3s, prob_t, p3);
	}
	else {
		size_t d = slots * slots * r3 + slots * (r1 - 1) + r2, e = (slots - r2) * (slots + 1 - r1) * r3s + (slots - r2) * (r1s + 1) + r2s, f = (slots - r2) * (slots + 1 - r1) * r3s + (slots - r2) * r1s + r2s;
		for (size_t c = 0; c < (r3 + 1) * (r1 + 1) * (r2 + 1); c++)
			prob_t[p1][a][b][c] = p * find_prob(d, e, c, r1, r2, r3, r1s, r2s, r3s, r1 - 1, r2, r3, r1s + 1, r2s, r3s, prob_t, p2) + (1 - p) * find_prob(d, f, c, r1, r2, r3, r1s, r2s, r3s, r1 - 1, r2, r3, r1s, r2s, r3s, prob_t, p3);
	}
}

void initcalcProbabilities(size_t slots, bool base_d[6][200], std::vector<std::vector<std::vector<std::vector<long double>>>>& prob_t) {
	for (size_t r3 = 0; r3 < slots; r3++) //(0,0,0)
		for (size_t r1 = 0; r1 < slots; r1++)
			for (size_t r2 = 0; r2 < slots; r2++) {
				size_t a = slots * slots * r3 + slots * r1 + r2;
				for (size_t prob_i = 0; prob_i < 6; prob_i++)
					prob_t[prob_i][0][a][0] = 1;
			}
	for (size_t r3 = 1; r3 < slots; r3++) //(0,0,r3)
		for (size_t r3s = 0; r3s < slots - r3; r3s++)
			for (size_t r1s = 0; r1s < slots; r1s++)
				for (size_t r2s = 0; r2s < slots; r2s++) {
					size_t a = slots * slots * r3, b = slots * slots * r3s + slots * r1s + r2s, c = slots * slots * (r3 - 1), d = slots * slots * (r3s + 1) + slots * r1s + r2s;
					for (size_t z = 0; z < r3 + 1; z++)
						for (size_t prob_i = 0; prob_i < 6; prob_i++)
							prob_t[prob_i][a][b][z] = (0.25 + 0.1 * prob_i) * find_prob(c, d, r1s, r2s, r3s + z, 0, 0, r3 - 1, r1s, r2s, r3s + 1, prob_t, prob_i > 0 ? prob_i - 1 : 0) + (0.75 - 0.1 * prob_i) * find_prob(c, b, r1s, r2s, r3s + z, 0, 0, r3 - 1, r1s, r2s, r3s, prob_t, prob_i < 5 ? prob_i + 1 : 5);
				}
	for (size_t r1 = 1; r1 < slots; r1++) //(r1,0,0)
		for (size_t r3s = 0; r3s < slots; r3s++)
			for (size_t r1s = 0; r1s < slots - r1; r1s++)
				for (size_t r2s = 0; r2s < slots; r2s++) {
					size_t a = slots * r1, b = slots * (slots - r1) * r3s + slots * r1s + r2s, c = slots * (r1 - 1), d = slots * (slots + 1 - r1) * r3s + slots * (r1s + 1) + r2s, e = slots * (slots + 1 - r1) * r3s + slots * r1s + r2s;
					for (size_t z = 0; z < r1 + 1; z++)
						for (size_t prob_i = 0; prob_i < 6; prob_i++)
							prob_t[prob_i][a][b][z] = (0.25 + 0.1 * prob_i) * find_prob(c, d, r1s + z, r2s, r3s, r1 - 1, 0, 0, r1s + 1, r2s, r3s, prob_t, prob_i > 0 ? prob_i - 1 : 0) + (0.75 - 0.1 * prob_i) * find_prob(c, e, r1s + z, r2s, r3s, r1 - 1, 0, 0, r1s, r2s, r3s, prob_t, prob_i < 5 ? prob_i + 1 : 5);
				}
	for (size_t r2 = 1; r2 < slots; r2++) //(0,r2,0)
		for (size_t r3s = 0; r3s < slots; r3s++)
			for (size_t r1s = 0; r1s < slots; r1s++)
				for (size_t r2s = 0; r2s < slots - r2; r2s++) {
					size_t a = slots * (slots - r2) * r3s + (slots - r2) * r1s + r2s, b = slots * (slots + 1 - r2) * r3s + (slots + 1 - r2) * r1s + r2s;
					for (size_t z = 0; z < r2 + 1; z++)
						for (size_t prob_i = 0; prob_i < 6; prob_i++)
							prob_t[prob_i][r2][a][z] = (0.25 + 0.1 * prob_i) * find_prob(r2 - 1, b + 1, r1s, r2s + z, r3s, 0, r2 - 1, 0, r1s, r2s + 1, r3s, prob_t, prob_i > 0 ? prob_i - 1 : 0) + (0.75 - 0.1 * prob_i) * find_prob(r2 - 1, b, r1s, r2s + z, r3s, 0, r2 - 1, 0, r1s, r2s, r3s, prob_t, prob_i < 5 ? prob_i + 1 : 5);
				}
	for (size_t r3 = 1; r3 < slots; r3++) //(r1,0,r3)
		for (size_t r1 = 1; r1 < slots; r1++)
			for (size_t r3s = 0; r3s < slots - r3; r3s++)
				for (size_t r1s = 0; r1s < slots - r1; r1s++)
					for (size_t r2s = 0; r2s < slots; r2s++)
						for (size_t prob_i = 0; prob_i < 6; prob_i++)
							func5(slots, r3, r1, r3s, r1s, r2s, 0.25 + 0.1 * prob_i, base_d, prob_t, prob_i, prob_i > 0 ? prob_i - 1 : 0, prob_i < 5 ? prob_i + 1 : 5);
	for (size_t r3 = 1; r3 < slots; r3++) //(0,r2,r3)
		for (size_t r2 = 1; r2 < slots; r2++)
			for (size_t r3s = 0; r3s < slots - r3; r3s++)
				for (size_t r1s = 0; r1s < slots; r1s++)
					for (size_t r2s = 0; r2s < slots - r2; r2s++)
						for (size_t prob_i = 0; prob_i < 6; prob_i++)
							func6(slots, r3, r2, r3s, r1s, r2s, 0.25 + 0.1 * prob_i, base_d, prob_t, prob_i, prob_i > 0 ? prob_i - 1 : 0, prob_i < 5 ? prob_i + 1 : 5);
}

void calcProbabilities(size_t r3, size_t r1, size_t slots, std::vector<std::vector<std::vector<int>>>& dt, std::vector<std::vector<std::vector<std::vector<long double>>>>& prob_t) {
	for (size_t r2 = 1; r2 < slots; r2++) //(r1,r2,r3)
		for (size_t r3s = 0; r3s < slots - r3; r3s++)
			for (size_t r1s = 0; r1s < slots - r1; r1s++)
				for (size_t r2s = 0; r2s < slots - r2; r2s++)
					for (size_t prob_i = 0; prob_i < 6; prob_i++)
						func7(slots, r3, r1, r2, r1s, r2s, r3s, 0.25 + 0.1 * prob_i, dt, prob_t, prob_i, prob_i > 0 ? prob_i - 1 : 0, prob_i < 5 ? prob_i + 1 : 5);
}

void func8(size_t r1c, size_t r2c, size_t slots, size_t r3, size_t r1, size_t r2, size_t r1s, size_t r2s, size_t r3s, long double p, long double w1, std::vector<std::vector<std::vector<int>>>& dt, std::vector<std::vector<std::vector<std::vector<long double>>>>& exp, std::vector<std::vector<std::vector<std::vector<long double>>>>& prob_t, size_t p1, size_t p2, size_t p3) {
	size_t a = slots * slots * r3 + slots * r1 + r2, b = (slots - r2) * (slots - r1) * r3s + (slots - r2) * r1s + r2s;
	if (dt[p1][a][(slots - r2) * r1s + r2s] == -1) {
		if (r1s >= r1c && r2s < r2c)
			w1 = 0;
		else if (r2s >= r2c && r1s < r1c)
			w1 = 1;
		//evaluate E(row 1) and E(row 2) when rolling row 1 then calculate absolute error from desired weight distribution
		long double i = p + p * exp[p2][slots * slots * r3 + slots * (r1 - 1) + r2][(slots - r2) * (r1s + 1) + r2s][0] + (1 - p) * exp[p3][slots * slots * r3 + slots * (r1 - 1) + r2][(slots - r2) * r1s + r2s][0];
		long double j = p * exp[p2][slots * slots * r3 + slots * (r1 - 1) + r2][(slots - r2) * (r1s + 1) + r2s][1] + (1 - p) * exp[p3][slots * slots * r3 + slots * (r1 - 1) + r2][(slots - r2) * r1s + r2s][1];
		long double r1error = abs(r1s + i - w1 * (r1s + i + r2s + j)) + abs(r2s + j - (1 - w1) * (r1s + i + r2s + j));
		//evaluate E(row 1) and E(row 2) when choosing row 2
		long double k = p * exp[p2][a - 1][(slots + 1 - r2) * r1s + r2s + 1][0] + (1 - p) * exp[p3][a - 1][(slots + 1 - r2) * r1s + r2s][0];
		long double l = p + p * exp[p2][a - 1][(slots + 1 - r2) * r1s + r2s + 1][1] + (1 - p) * exp[p3][a - 1][(slots + 1 - r2) * r1s + r2s][1];
		long double r2error = abs(r1s + k - w1 * (r1s + k + r2s + l)) + abs(r2s + l - (1 - w1) * (r1s + k + r2s + l));
		if (r1error < r2error) {
			dt[p1][a][(slots - r2) * r1s + r2s] = 0;
			exp[p1][a][(slots - r2) * r1s + r2s][0] = i;
			exp[p1][a][(slots - r2) * r1s + r2s][1] = j;
			size_t d = slots * slots * r3 + slots * (r1 - 1) + r2, e = (slots - r2) * (slots + 1 - r1) * r3s + (slots - r2) * (r1s + 1) + r2s, f = (slots - r2) * (slots + 1 - r1) * r3s + (slots - r2) * r1s + r2s;
			for (size_t c = 0; c < (r3 + 1) * (r1 + 1) * (r2 + 1); c++)
				prob_t[p1][a][b][c] = p * find_prob(d, e, c, r1, r2, r3, r1s, r2s, r3s, r1 - 1, r2, r3, r1s + 1, r2s, r3s, prob_t, p2) + (1 - p) * find_prob(d, f, c, r1, r2, r3, r1s, r2s, r3s, r1 - 1, r2, r3, r1s, r2s, r3s, prob_t, p3);
		}
		else if (r1error > r2error) {
			dt[p1][a][(slots - r2) * r1s + r2s] = 1;
			exp[p1][a][(slots - r2) * r1s + r2s][0] = k;
			exp[p1][a][(slots - r2) * r1s + r2s][1] = l;
			size_t d = (slots + 1 - r2) * (slots - r1) * r3s + (slots + 1 - r2) * r1s + r2s;
			for (size_t c = 0; c < (r3 + 1) * (r1 + 1) * (r2 + 1); c++)
				prob_t[p1][a][b][c] = p * find_prob(a - 1, d + 1, c, r1, r2, r3, r1s, r2s, r3s, r1, r2 - 1, r3, r1s, r2s + 1, r3s, prob_t, p2) + (1 - p) * find_prob(a - 1, d, c, r1, r2, r3, r1s, r2s, r3s, r1, r2 - 1, r3, r1s, r2s, r3s, prob_t, p3);
		}
		else {
			dt[p1][a][(slots - r2) * r1s + r2s] = 3;
			exp[p1][a][(slots - r2) * r1s + r2s][0] = i; //doesn't have a preference
			exp[p1][a][(slots - r2) * r1s + r2s][1] = l;
			size_t d = slots * slots * r3 + slots * (r1 - 1) + r2, e = (slots - r2) * (slots + 1 - r1) * r3s + (slots - r2) * (r1s + 1) + r2s, f = (slots - r2) * (slots + 1 - r1) * r3s + (slots - r2) * r1s + r2s;
			for (size_t c = 0; c < (r3 + 1) * (r1 + 1) * (r2 + 1); c++)
				prob_t[p1][a][b][c] = p * find_prob(d, e, c, r1, r2, r3, r1s, r2s, r3s, r1 - 1, r2, r3, r1s + 1, r2s, r3s, prob_t, p2) + (1 - p) * find_prob(d, f, c, r1, r2, r3, r1s, r2s, r3s, r1 - 1, r2, r3, r1s, r2s, r3s, prob_t, p3);
		}
	}
	else if (dt[p1][a][(slots - r2) * r1s + r2s] == 1) {
		size_t d = (slots + 1 - r2) * (slots - r1) * r3s + (slots + 1 - r2) * r1s + r2s;
		for (size_t c = 0; c < (r3 + 1) * (r1 + 1) * (r2 + 1); c++)
			prob_t[p1][a][b][c] = p * find_prob(a - 1, d + 1, c, r1, r2, r3, r1s, r2s, r3s, r1, r2 - 1, r3, r1s, r2s + 1, r3s, prob_t, p2) + (1 - p) * find_prob(a - 1, d, c, r1, r2, r3, r1s, r2s, r3s, r1, r2 - 1, r3, r1s, r2s, r3s, prob_t, p3);
	}
	else {
		size_t d = slots * slots * r3 + slots * (r1 - 1) + r2, e = (slots - r2) * (slots + 1 - r1) * r3s + (slots - r2) * (r1s + 1) + r2s, f = (slots - r2) * (slots + 1 - r1) * r3s + (slots - r2) * r1s + r2s;
		for (size_t c = 0; c < (r3 + 1) * (r1 + 1) * (r2 + 1); c++)
			prob_t[p1][a][b][c] = p * find_prob(d, e, c, r1, r2, r3, r1s, r2s, r3s, r1 - 1, r2, r3, r1s + 1, r2s, r3s, prob_t, p2) + (1 - p) * find_prob(d, f, c, r1, r2, r3, r1s, r2s, r3s, r1 - 1, r2, r3, r1s, r2s, r3s, prob_t, p3);
	}
}

long double applyconditions(size_t r1c, size_t r2c, size_t i, size_t j, size_t coord, size_t r1, size_t r2, size_t r3, size_t r1s, size_t r2s, size_t r3s, std::vector<std::vector<std::vector<std::vector<long double>>>>& prob_t, size_t prob_i) {
	size_t r1p = 0, r2p = 0, r3p = 0; //translate coordinate to r1p, r2p, r3p
	if (r1 == 0) {
		r1p = r1s;
		if (r2 == 0) {
			r2p = r2s;
			r3p = coord + r3s;
			if (r1p >= r1c && r2p >= r2c)
				return prob_t[prob_i][i][j][r3p - r3s];
			return 0;
		}
		else if (r3 == 0) {
			r3p = r3s;
			r2p = coord + r2s;
			if (r1p >= r1c && r2p >= r2c)
				return prob_t[prob_i][i][j][r2p - r2s];
			return 0;
		}
		else { //r2p is column, r3p is row
			r3p = r3s + coord / (r2 + 1);
			r2p = r2s + coord % (r2 + 1);
			if (r1p >= r1c && r2p >= r2c)
				return prob_t[prob_i][i][j][(r2 + 1) * (r3p - r3s) + r2p - r2s];
			return 0;
		}
	}
	else if (r2 == 0) {
		r2p = r2s;
		if (r3 == 0) {
			r3p = r3s;
			r1p = coord + r1s;
			if (r1p >= r1c && r2p >= r2c)
				return prob_t[prob_i][i][j][r1p - r1s];
			return 0;
		}
		else { //r1p is column, r3p is row
			r3p = r3s + coord / (r1 + 1);
			r1p = r1s + coord % (r1 + 1);
			if (r1p >= r1c && r2p >= r2c)
				return prob_t[prob_i][i][j][(r1 + 1) * (r3p - r3s) + r1p - r1s];
			return 0;
		}
	}
	else if (r3 == 0) {
		r3p = r3s; //r2p is column, r1p is row
		r1p = r1s + coord / (r2 + 1);
		r2p = r2s + coord % (r2 + 1);
		if (r1p >= r1c && r2p >= r2c)
			return prob_t[prob_i][i][j][(r2 + 1) * (r1p - r1s) + r2p - r2s];
		return 0;
	}
	else { //r2p is column, r1p is row, r3p is depth
		size_t s = (r1 + 1) * (r2 + 1);
		size_t t = coord % s;
		r3p = r3s + coord / s;
		r1p = r1s + t / (r2 + 1);
		r2p = r2s + t % (r2 + 1);
		if (r1p >= r1c && r2p >= r2c)
			return prob_t[prob_i][i][j][(r1 + 1) * (r2 + 1) * (r3p - r3s) + (r2 + 1) * (r1p - r1s) + r2p - r2s];
		return 0;
	}
	return 0;
}

void func9(size_t r1c, size_t r2c, size_t slots, size_t r3, size_t r1, size_t r2, size_t r1s, size_t r2s, size_t r3s, long double p, long double w1, std::vector<std::vector<std::vector<int>>>& dt, std::vector<std::vector<std::vector<std::vector<long double>>>>& exp, std::vector<std::vector<std::vector<std::vector<long double>>>>& prob_t, size_t p1, size_t p2, size_t p3) {
	size_t a = slots * slots * r3 + slots * r1 + r2, b = (slots - r2) * (slots - r1) * r3s + (slots - r2) * r1s + r2s, g = (slots + 1 - r2) * (slots - r1) * r3s + (slots + 1 - r2) * r1s + r2s;
	size_t d = slots * slots * r3 + slots * (r1 - 1) + r2, e = (slots - r2) * (slots + 1 - r1) * r3s + (slots - r2) * (r1s + 1) + r2s, f = (slots - r2) * (slots + 1 - r1) * r3s + (slots - r2) * r1s + r2s;
	long double s1 = 0, s2 = 0, s3 = 0, s4 = 0; //calculate pr1c,r2c for picking row 1, which can succeed or fail
	for (size_t c = 0; c < (r3 + 1) * r1 * (r2 + 1); c++) {
		s1 += applyconditions(r1c, r2c, d, e, c, r1 - 1, r2, r3, r1s + 1, r2s, r3s, prob_t, p2); //success case
		s2 += applyconditions(r1c, r2c, d, f, c, r1 - 1, r2, r3, r1s, r2s, r3s, prob_t, p3); //fail case
	}
	for (size_t c = 0; c < (r3 + 1) * (r1 + 1) * r2; c++) { //calculate pr1c,r2c for picking row 2, which can succeed or fail
		s3 += applyconditions(r1c, r2c, a - 1, g + 1, c, r1, r2 - 1, r3, r1s, r2s + 1, r3s, prob_t, p2); //success case
		s4 += applyconditions(r1c, r2c, a - 1, g, c, r1, r2 - 1, r3, r1s, r2s, r3s, prob_t, p3); //fail case
	}
	if (p * s1 + (1 - p) * s2 > p * s3 + (1 - p) * s4) {
		if (dt[p1][a][(slots - r2) * r1s + r2s] == -1) {
			dt[p1][a][(slots - r2) * r1s + r2s] = 0;
			exp[p1][a][(slots - r2) * r1s + r2s][0] = p + p * exp[p2][d][(slots - r2) * (r1s + 1) + r2s][0] + (1 - p) * exp[p3][d][(slots - r2) * r1s + r2s][0];
			exp[p1][a][(slots - r2) * r1s + r2s][1] = p * exp[p2][d][(slots - r2) * (r1s + 1) + r2s][1] + (1 - p) * exp[p3][d][(slots - r2) * r1s + r2s][1];
		}
		for (size_t c = 0; c < (r3 + 1) * (r1 + 1) * (r2 + 1); c++)
			prob_t[p1][a][b][c] = p * find_prob(d, e, c, r1, r2, r3, r1s, r2s, r3s, r1 - 1, r2, r3, r1s + 1, r2s, r3s, prob_t, p2) + (1 - p) * find_prob(d, f, c, r1, r2, r3, r1s, r2s, r3s, r1 - 1, r2, r3, r1s, r2s, r3s, prob_t, p3);
	}
	else if (p * s1 + (1 - p) * s2 < p * s3 + (1 - p) * s4) {
		if (dt[p1][a][(slots - r2) * r1s + r2s] == -1) {
			dt[p1][a][(slots - r2) * r1s + r2s] = 1;
			exp[p1][a][(slots - r2) * r1s + r2s][0] = p * exp[p2][a - 1][(slots + 1 - r2) * r1s + r2s + 1][0] + (1 - p) * exp[p3][a - 1][(slots + 1 - r2) * r1s + r2s][0];
			exp[p1][a][(slots - r2) * r1s + r2s][1] = p + p * exp[p2][a - 1][(slots + 1 - r2) * r1s + r2s + 1][1] + (1 - p) * exp[p3][a - 1][(slots + 1 - r2) * r1s + r2s][1];
		}
		for (size_t c = 0; c < (r3 + 1) * (r1 + 1) * (r2 + 1); c++)
			prob_t[p1][a][b][c] = p * find_prob(a - 1, g + 1, c, r1, r2, r3, r1s, r2s, r3s, r1, r2 - 1, r3, r1s, r2s + 1, r3s, prob_t, p2) + (1 - p) * find_prob(a - 1, g, c, r1, r2, r3, r1s, r2s, r3s, r1, r2 - 1, r3, r1s, r2s, r3s, prob_t, p3);
	} //can have a situation where picking row 1 is as good as picking row 2
	else func8(r1c, r2c, slots, r3, r1, r2, r1s, r2s, r3s, p, w1, dt, exp, prob_t, p1, p2, p3);
}

void func10(size_t r1c, size_t r2c, size_t slots, size_t r3, size_t r1, size_t r2, size_t r1s, size_t r2s, size_t r3s, long double p, long double w1, bool base_d[6][200], std::vector<std::vector<std::vector<int>>>& dt, std::vector<std::vector<std::vector<std::vector<long double>>>>& exp, std::vector<std::vector<std::vector<std::vector<long double>>>>& prob_t, size_t p1, size_t p2, size_t p3) {
	if (r3 == 0 || base_d[p1][20 * (r3 - 1) + r1 + r2 - 1]) { //choose row 1 or row 2
		if (r1s + r1 < r1c || r2s + r2 < r2c) { //if conditions cannot be met, then adjust the one(s) that cannot be met (r1c and/or r2c) to the maximum value(s) that can be met
			if (r1s + r1 < r1c)
				r1c = r1s + r1;
			if (r2s + r2 < r2c)
				r2c = r2s + r2;
			func9(r1c, r2c, slots, r3, r1, r2, r1s, r2s, r3s, p, w1, dt, exp, prob_t, p1, p2, p3);
		} //if conditions are already met for both, then either use weights or adjust r1s and/or r2s to a higher value that can be met
		else if (r1s >= r1c && r2s >= r2c)
			func8(r1c, r2c, slots, r3, r1, r2, r1s, r2s, r3s, p, w1, dt, exp, prob_t, p1, p2, p3);
		else func9(r1c, r2c, slots, r3, r1, r2, r1s, r2s, r3s, p, w1, dt, exp, prob_t, p1, p2, p3);
	}
	else { //choose row 3
		size_t a = slots * slots * r3 + slots * r1 + r2, b = (slots - r2) * (slots - r1) * r3s + (slots - r2) * r1s + r2s;
		if (dt[p1][a][(slots - r2) * r1s + r2s] == -1) {
			dt[p1][a][(slots - r2) * r1s + r2s] = 2;
			exp[p1][a][(slots - r2) * r1s + r2s][0] = p * exp[p2][slots * slots * (r3 - 1) + slots * r1 + r2][(slots - r2) * r1s + r2s][0] + (1 - p) * exp[p3][slots * slots * (r3 - 1) + slots * r1 + r2][(slots - r2) * r1s + r2s][0];
			exp[p1][a][(slots - r2) * r1s + r2s][1] = p * exp[p2][slots * slots * (r3 - 1) + slots * r1 + r2][(slots - r2) * r1s + r2s][1] + (1 - p) * exp[p3][slots * slots * (r3 - 1) + slots * r1 + r2][(slots - r2) * r1s + r2s][1];
		}
		size_t d = slots * slots * (r3 - 1) + slots * r1 + r2, e = (slots - r2) * (slots - r1) * (r3s + 1) + (slots - r2) * r1s + r2s;
		for (size_t c = 0; c < (r3 + 1) * (r1 + 1) * (r2 + 1); c++)
			prob_t[p1][a][b][c] = p * find_prob(d, e, c, r1, r2, r3, r1s, r2s, r3s, r1, r2, r3 - 1, r1s, r2s, r3s + 1, prob_t, p2) + (1 - p) * find_prob(d, b, c, r1, r2, r3, r1s, r2s, r3s, r1, r2, r3 - 1, r1s, r2s, r3s, prob_t, p3);
	}
}

void initcalcTable2(size_t slots, bool base_d[6][200], std::vector<std::vector<std::vector<int>>>& dt, std::vector<std::vector<std::vector<std::vector<long double>>>>& exp, std::vector<std::vector<std::vector<std::vector<long double>>>>& prob_t) {
	for (size_t r3s = 0; r3s < slots; r3s++) //(0,0,0)
		for (size_t r1s = 0; r1s < slots; r1s++)
			for (size_t r2s = 0; r2s < slots; r2s++) {
				size_t a = slots * slots * r3s + slots * r1s + r2s;
				for (size_t prob_i = 0; prob_i < 6; prob_i++)
					prob_t[prob_i][0][a][0] = 1;
			}
	for (size_t r3 = 1; r3 < slots; r3++) //(0,0,r3)
		for (size_t r1s = 0; r1s < slots; r1s++)
			for (size_t r2s = 0; r2s < slots; r2s++)
				for (size_t prob_i = 0; prob_i < 6; prob_i++) {
					dt[prob_i][slots * slots * r3][slots * r1s + r2s] = 2;
					exp[prob_i][slots * slots * r3][slots * r1s + r2s][0] = 0;
					exp[prob_i][slots * slots * r3][slots * r1s + r2s][1] = 0;
				}
	for (size_t r3 = 1; r3 < slots; r3++) //(0,0,r3)
		for (size_t r3s = 0; r3s < slots - r3; r3s++)
			for (size_t r1s = 0; r1s < slots; r1s++)
				for (size_t r2s = 0; r2s < slots; r2s++) {
					size_t a = slots * slots * r3, b = slots * slots * r3s + slots * r1s + r2s, c = slots * slots * (r3 - 1), d = slots * slots * (r3s + 1) + slots * r1s + r2s;
					for (size_t z = 0; z < r3 + 1; z++)
						for (size_t prob_i = 0; prob_i < 6; prob_i++)
							prob_t[prob_i][a][b][z] = (0.25 + 0.1 * prob_i) * find_prob(c, d, r1s, r2s, r3s + z, 0, 0, r3 - 1, r1s, r2s, r3s + 1, prob_t, prob_i > 0 ? prob_i - 1 : 0) + (0.75 - 0.1 * prob_i) * find_prob(c, b, r1s, r2s, r3s + z, 0, 0, r3 - 1, r1s, r2s, r3s, prob_t, prob_i < 5 ? prob_i + 1 : 5);
				}
	for (size_t r1 = 1; r1 < slots; r1++) //(r1,0,0)
		for (size_t r1s = 0; r1s < slots - r1; r1s++)
			for (size_t r2s = 0; r2s < slots; r2s++)
				for (size_t prob_i = 0; prob_i < 6; prob_i++) {
					exp[prob_i][slots * r1][slots * r1s + r2s][0] = 0.25 + 0.1 * prob_i + (0.25 + 0.1 * prob_i) * exp[prob_i > 0 ? prob_i - 1 : 0][slots * (r1 - 1)][slots * (r1s + 1) + r2s][0] + (0.75 - 0.1 * prob_i) * exp[prob_i < 5 ? prob_i + 1 : 5][slots * (r1 - 1)][slots * r1s + r2s][0];
					exp[prob_i][slots * r1][slots * r1s + r2s][1] = 0;
					dt[prob_i][slots * r1][slots * r1s + r2s] = 0;
				}
	for (size_t r1 = 1; r1 < slots; r1++) //(r1,0,0)
		for (size_t r3s = 0; r3s < slots; r3s++)
			for (size_t r1s = 0; r1s < slots - r1; r1s++)
				for (size_t r2s = 0; r2s < slots; r2s++) {
					size_t a = slots * r1, b = slots * (slots - r1) * r3s + slots * r1s + r2s, c = slots * (r1 - 1), d = slots * (slots + 1 - r1) * r3s + slots * (r1s + 1) + r2s, e = slots * (slots + 1 - r1) * r3s + slots * r1s + r2s;
					for (size_t z = 0; z < r1 + 1; z++)
						for (size_t prob_i = 0; prob_i < 6; prob_i++)
							prob_t[prob_i][a][b][z] = (0.25 + 0.1 * prob_i) * find_prob(c, d, r1s + z, r2s, r3s, r1 - 1, 0, 0, r1s + 1, r2s, r3s, prob_t, prob_i > 0 ? prob_i - 1 : 0) + (0.75 - 0.1 * prob_i) * find_prob(c, e, r1s + z, r2s, r3s, r1 - 1, 0, 0, r1s, r2s, r3s, prob_t, prob_i < 5 ? prob_i + 1 : 5);
				}
	for (size_t r2 = 1; r2 < slots; r2++) //(0,r2,0)
		for (size_t r1s = 0; r1s < slots; r1s++)
			for (size_t r2s = 0; r2s < slots - r2; r2s++)
				for (size_t prob_i = 0; prob_i < 6; prob_i++) {
					exp[prob_i][r2][(slots - r2) * r1s + r2s][1] = 0.25 + 0.1 * prob_i + (0.25 + 0.1 * prob_i) * exp[prob_i > 0 ? prob_i - 1 : 0][r2 - 1][(slots + 1 - r2) * r1s + r2s + 1][1] + (0.75 - 0.1 * prob_i) * exp[prob_i < 5 ? prob_i + 1 : 5][r2 - 1][(slots + 1 - r2) * r1s + r2s][1];
					exp[prob_i][r2][(slots - r2) * r1s + r2s][0] = 0;
					dt[prob_i][r2][(slots - r2) * r1s + r2s] = 1;
				}
	for (size_t r2 = 1; r2 < slots; r2++) //(0,r2,0)
		for (size_t r3s = 0; r3s < slots; r3s++)
			for (size_t r1s = 0; r1s < slots; r1s++)
				for (size_t r2s = 0; r2s < slots - r2; r2s++) {
					size_t a = slots * (slots - r2) * r3s + (slots - r2) * r1s + r2s, b = slots * (slots + 1 - r2) * r3s + (slots + 1 - r2) * r1s + r2s;
					for (size_t z = 0; z < r2 + 1; z++)
						for (size_t prob_i = 0; prob_i < 6; prob_i++)
							prob_t[prob_i][r2][a][z] = (0.25 + 0.1 * prob_i) * find_prob(r2 - 1, b + 1, r1s, r2s + z, r3s, 0, r2 - 1, 0, r1s, r2s + 1, r3s, prob_t, prob_i > 0 ? prob_i - 1 : 0) + (0.75 - 0.1 * prob_i) * find_prob(r2 - 1, b, r1s, r2s + z, r3s, 0, r2 - 1, 0, r1s, r2s, r3s, prob_t, prob_i < 5 ? prob_i + 1 : 5);
				}
	for (size_t r3 = 1; r3 < slots; r3++) //(r1,0,r3)
		for (size_t r1 = 1; r1 < slots; r1++)
			for (size_t r1s = 0; r1s < slots - r1; r1s++)
				for (size_t r2s = 0; r2s < slots; r2s++)
					for (size_t prob_i = 0; prob_i < 6; prob_i++)
						func2(slots, r3, r1, r1s, r2s, 0.25 + 0.1 * prob_i, base_d, dt, exp, prob_i, prob_i > 0 ? prob_i - 1 : 0, prob_i < 5 ? prob_i + 1 : 5);
	for (size_t r3 = 1; r3 < slots; r3++) //(r1,0,r3)
		for (size_t r1 = 1; r1 < slots; r1++)
			for (size_t r3s = 0; r3s < slots - r3; r3s++)
				for (size_t r1s = 0; r1s < slots - r1; r1s++)
					for (size_t r2s = 0; r2s < slots; r2s++)
						for (size_t prob_i = 0; prob_i < 6; prob_i++)
							func5(slots, r3, r1, r3s, r1s, r2s, 0.25 + 0.1 * prob_i, base_d, prob_t, prob_i, prob_i > 0 ? prob_i - 1 : 0, prob_i < 5 ? prob_i + 1 : 5);
	for (size_t r3 = 1; r3 < slots; r3++) //(0,r2,r3)
		for (size_t r2 = 1; r2 < slots; r2++)
			for (size_t r1s = 0; r1s < slots; r1s++)
				for (size_t r2s = 0; r2s < slots - r2; r2s++)
					for (size_t prob_i = 0; prob_i < 6; prob_i++)
						func3(slots, r3, r2, r1s, r2s, 0.25 + 0.1 * prob_i, base_d, dt, exp, prob_i, prob_i > 0 ? prob_i - 1 : 0, prob_i < 5 ? prob_i + 1 : 5);
	for (size_t r3 = 1; r3 < slots; r3++) //(0,r2,r3)
		for (size_t r2 = 1; r2 < slots; r2++)
			for (size_t r3s = 0; r3s < slots - r3; r3s++)
				for (size_t r1s = 0; r1s < slots; r1s++)
					for (size_t r2s = 0; r2s < slots - r2; r2s++)
						for (size_t prob_i = 0; prob_i < 6; prob_i++)
							func6(slots, r3, r2, r3s, r1s, r2s, 0.25 + 0.1 * prob_i, base_d, prob_t, prob_i, prob_i > 0 ? prob_i - 1 : 0, prob_i < 5 ? prob_i + 1 : 5);
	for (size_t r3 = 0; r3 < slots; r3++) //(r1,r2,r3)
		for (size_t r1 = 1; r1 < slots; r1++)
			for (size_t r2 = 1; r2 < slots; r2++)
				for (size_t r3s = 0; r3s < slots - r3; r3s++)
					for (size_t r1s = 0; r1s < slots - r1; r1s++)
						for (size_t r2s = 0; r2s < slots - r2; r2s++)
							for (size_t prob_i = 0; prob_i < 6; prob_i++)
								dt[prob_i][slots * slots * r3 + slots * r1 + r2][(slots - r2) * r1s + r2s] = -1;
}

void calcTable2(size_t r3, size_t r1, size_t r1c, size_t r2c, size_t slots, bool base_d[6][200], long double w1, std::vector<std::vector<std::vector<int>>>& dt, std::vector<std::vector<std::vector<std::vector<long double>>>>& exp, std::vector<std::vector<std::vector<std::vector<long double>>>>& prob_t) {
	for (size_t r2 = 1; r2 < slots; r2++) //(r1,r2,r3)
		for (size_t r3s = 0; r3s < slots - r3; r3s++)
			for (size_t r1s = 0; r1s < slots - r1; r1s++)
				for (size_t r2s = 0; r2s < slots - r2; r2s++)
					for (size_t prob_i = 0; prob_i < 6; prob_i++)
						func10(r1c, r2c, slots, r3, r1, r2, r1s, r2s, r3s, 0.25 + 0.1 * prob_i, w1, base_d, dt, exp, prob_t, prob_i, prob_i > 0 ? prob_i - 1 : 0, prob_i < 5 ? prob_i + 1 : 5);
}

long double applyconditions2(size_t r1c, size_t r2c, size_t r3c, size_t i, size_t j, size_t coord, size_t r1, size_t r2, size_t r3, size_t r1s, size_t r2s, size_t r3s, std::vector<std::vector<std::vector<std::vector<long double>>>>& prob_t, size_t prob_i) {
	size_t r1p = 0, r2p = 0, r3p = 0; //translate coordinate to r1p, r2p, r3p
	if (r1 == 0) {
		r1p = r1s;
		if (r2 == 0) {
			r2p = r2s;
			r3p = coord + r3s;
			if (r1p >= r1c && r2p >= r2c && r3p <= r3c)
				return prob_t[prob_i][i][j][r3p - r3s];
			return 0;
		}
		else if (r3 == 0) {
			r3p = r3s;
			r2p = coord + r2s;
			if (r1p >= r1c && r2p >= r2c && r3p <= r3c)
				return prob_t[prob_i][i][j][r2p - r2s];
			return 0;
		}
		else { //r2p is column, r3p is row
			r3p = r3s + coord / (r2 + 1);
			r2p = r2s + coord % (r2 + 1);
			if (r1p >= r1c && r2p >= r2c && r3p <= r3c)
				return prob_t[prob_i][i][j][(r2 + 1) * (r3p - r3s) + r2p - r2s];
			return 0;
		}
	}
	else if (r2 == 0) {
		r2p = r2s;
		if (r3 == 0) {
			r3p = r3s;
			r1p = coord + r1s;
			if (r1p >= r1c && r2p >= r2c && r3p <= r3c)
				return prob_t[prob_i][i][j][r1p - r1s];
			return 0;
		}
		else { //r1p is column, r3p is row
			r3p = r3s + coord / (r1 + 1);
			r1p = r1s + coord % (r1 + 1);
			if (r1p >= r1c && r2p >= r2c && r3p <= r3c)
				return prob_t[prob_i][i][j][(r1 + 1) * (r3p - r3s) + r1p - r1s];
			return 0;
		}
	}
	else if (r3 == 0) {
		r3p = r3s; //r2p is column, r1p is row
		r1p = r1s + coord / (r2 + 1);
		r2p = r2s + coord % (r2 + 1);
		if (r1p >= r1c && r2p >= r2c && r3p <= r3c)
			return prob_t[prob_i][i][j][(r2 + 1) * (r1p - r1s) + r2p - r2s];
		return 0;
	}
	else { //r2p is column, r1p is row, r3p is depth
		size_t s = (r1 + 1) * (r2 + 1);
		size_t t = coord % s;
		r3p = r3s + coord / s;
		r1p = r1s + t / (r2 + 1);
		r2p = r2s + t % (r2 + 1);
		if (r1p >= r1c && r2p >= r2c && r3p <= r3c)
			return prob_t[prob_i][i][j][(r1 + 1) * (r2 + 1) * (r3p - r3s) + (r2 + 1) * (r1p - r1s) + r2p - r2s];
		return 0;
	}
	return 0;
}

void func14(size_t r1c, size_t r2c, size_t r3c, size_t slots, size_t r3, size_t r1, size_t r2, size_t r1s, size_t r2s, size_t r3s, long double p, long double w1, std::vector<std::vector<std::vector<int>>>& dt, std::vector<std::vector<std::vector<std::vector<long double>>>>& exp, std::vector<std::vector<std::vector<std::vector<long double>>>>& prob_t, size_t p1, size_t p2, size_t p3) {
	size_t a = slots * slots * r3 + slots * r1 + r2, b = (slots - r2) * (slots - r1) * r3s + (slots - r2) * r1s + r2s, g = (slots + 1 - r2) * (slots - r1) * r3s + (slots + 1 - r2) * r1s + r2s;
	size_t d = slots * slots * r3 + slots * (r1 - 1) + r2, e = (slots - r2) * (slots + 1 - r1) * r3s + (slots - r2) * (r1s + 1) + r2s, f = (slots - r2) * (slots + 1 - r1) * r3s + (slots - r2) * r1s + r2s;
	long double s1 = 0, s2 = 0, s3 = 0, s4 = 0, s5 = 0, s6 = 0;
	for (size_t c = 0; c < (r3 + 1) * r1 * (r2 + 1); c++) { //calculate pr1c,r2c,r3c for picking row 1, which can succeed or fail
		s1 += applyconditions2(r1c, r2c, r3c, d, e, c, r1 - 1, r2, r3, r1s + 1, r2s, r3s, prob_t, p2); //success case
		s2 += applyconditions2(r1c, r2c, r3c, d, f, c, r1 - 1, r2, r3, r1s, r2s, r3s, prob_t, p3); //fail case
	}
	for (size_t c = 0; c < (r3 + 1) * (r1 + 1) * r2; c++) { //calculate pr1c,r2c,r3c for picking row 2, which can succeed or fail
		s3 += applyconditions2(r1c, r2c, r3c, a - 1, g + 1, c, r1, r2 - 1, r3, r1s, r2s + 1, r3s, prob_t, p2); //success case
		s4 += applyconditions2(r1c, r2c, r3c, a - 1, g, c, r1, r2 - 1, r3, r1s, r2s, r3s, prob_t, p3); //fail case
	}
	size_t d1 = slots * slots * (r3 - 1) + slots * r1 + r2, e1 = (slots - r2) * (slots - r1) * (r3s + 1) + (slots - r2) * r1s + r2s;
	for (size_t c = 0; c < r3 * (r1 + 1) * (r2 + 1); c++) { //calculate pr1c,r2c,r3c for picking row 3, which can succeed or fail
		s5 += applyconditions2(r1c, r2c, r3c, d1, e1, c, r1, r2, r3 - 1, r1s, r2s, r3s + 1, prob_t, p2); //success case
		s6 += applyconditions2(r1c, r2c, r3c, d1, b, c, r1, r2, r3 - 1, r1s, r2s, r3s, prob_t, p3); //fail case
	}
	long double pp1 = p * s1 + (1 - p) * s2, pp2 = p * s3 + (1 - p) * s4, pp3 = p * s5 + (1 - p) * s6;
	if (pp1 > pp2 && pp1 > pp3) {
		if (dt[p1][a][(slots - r2) * r1s + r2s] == -1) {
			dt[p1][a][(slots - r2) * r1s + r2s] = 0;
			exp[p1][a][(slots - r2) * r1s + r2s][0] = p + p * exp[p2][d][(slots - r2) * (r1s + 1) + r2s][0] + (1 - p) * exp[p3][d][(slots - r2) * r1s + r2s][0];
			exp[p1][a][(slots - r2) * r1s + r2s][1] = p * exp[p2][d][(slots - r2) * (r1s + 1) + r2s][1] + (1 - p) * exp[p3][d][(slots - r2) * r1s + r2s][1];
		}
		for (size_t c = 0; c < (r3 + 1) * (r1 + 1) * (r2 + 1); c++)
			prob_t[p1][a][b][c] = p * find_prob(d, e, c, r1, r2, r3, r1s, r2s, r3s, r1 - 1, r2, r3, r1s + 1, r2s, r3s, prob_t, p2) + (1 - p) * find_prob(d, f, c, r1, r2, r3, r1s, r2s, r3s, r1 - 1, r2, r3, r1s, r2s, r3s, prob_t, p3);
	}
	else if (pp2 > pp1 && pp2 > pp3) {
		if (dt[p1][a][(slots - r2) * r1s + r2s] == -1) {
			dt[p1][a][(slots - r2) * r1s + r2s] = 1;
			exp[p1][a][(slots - r2) * r1s + r2s][0] = p * exp[p2][a - 1][(slots + 1 - r2) * r1s + r2s + 1][0] + (1 - p) * exp[p3][a - 1][(slots + 1 - r2) * r1s + r2s][0];
			exp[p1][a][(slots - r2) * r1s + r2s][1] = p + p * exp[p2][a - 1][(slots + 1 - r2) * r1s + r2s + 1][1] + (1 - p) * exp[p3][a - 1][(slots + 1 - r2) * r1s + r2s][1];
		}
		for (size_t c = 0; c < (r3 + 1) * (r1 + 1) * (r2 + 1); c++)
			prob_t[p1][a][b][c] = p * find_prob(a - 1, g + 1, c, r1, r2, r3, r1s, r2s, r3s, r1, r2 - 1, r3, r1s, r2s + 1, r3s, prob_t, p2) + (1 - p) * find_prob(a - 1, g, c, r1, r2, r3, r1s, r2s, r3s, r1, r2 - 1, r3, r1s, r2s, r3s, prob_t, p3);
	}
	else if (pp3 > pp1 && pp3 > pp2) {
		if (dt[p1][a][(slots - r2) * r1s + r2s] == -1) {
			dt[p1][a][(slots - r2) * r1s + r2s] = 2;
			exp[p1][a][(slots - r2) * r1s + r2s][0] = p * exp[p2][slots * slots * (r3 - 1) + slots * r1 + r2][(slots - r2) * r1s + r2s][0] + (1 - p) * exp[p3][slots * slots * (r3 - 1) + slots * r1 + r2][(slots - r2) * r1s + r2s][0];
			exp[p1][a][(slots - r2) * r1s + r2s][1] = p * exp[p2][slots * slots * (r3 - 1) + slots * r1 + r2][(slots - r2) * r1s + r2s][1] + (1 - p) * exp[p3][slots * slots * (r3 - 1) + slots * r1 + r2][(slots - r2) * r1s + r2s][1];
		}
		for (size_t c = 0; c < (r3 + 1) * (r1 + 1) * (r2 + 1); c++)
			prob_t[p1][a][b][c] = p * find_prob(d1, e1, c, r1, r2, r3, r1s, r2s, r3s, r1, r2, r3 - 1, r1s, r2s, r3s + 1, prob_t, p2) + (1 - p) * find_prob(d1, b, c, r1, r2, r3, r1s, r2s, r3s, r1, r2, r3 - 1, r1s, r2s, r3s, prob_t, p3);
	} //if there exists a situation where picking any row gives the same score
	else func8(r1c, r2c, slots, r3, r1, r2, r1s, r2s, r3s, p, w1, dt, exp, prob_t, p1, p2, p3);
}

void func15(size_t r1c, size_t r2c, size_t r3c, size_t slots, size_t r3, size_t r1, size_t r2, size_t r1s, size_t r2s, size_t r3s, long double p, long double w1, bool base_d[6][200], std::vector<std::vector<std::vector<int>>>& dt, std::vector<std::vector<std::vector<std::vector<long double>>>>& exp, std::vector<std::vector<std::vector<std::vector<long double>>>>& prob_t, size_t p1, size_t p2, size_t p3) {
	if (r1s + r1 < r1c || r2s + r2 < r2c || r3s + r3 > r3c) { //if conditions cannot be met, then adjust the one(s) that cannot be met (r1c and/or r2c and/or r3c) to the nearest value(s) that can be met
		if (r1s + r1 < r1c)
			r1c = r1s + r1;
		if (r2s + r2 < r2c)
			r2c = r2s + r2;
		if (r3s + r3 > r3c)
			r3c = r3s + r3;
		func14(r1c, r2c, r3c, slots, r3, r1, r2, r1s, r2s, r3s, p, w1, dt, exp, prob_t, p1, p2, p3);
	} //if conditions are already met for both, then use weights (could adjust r1s and/or r2s and/or r3s to a better value that can be met)
	else if (r1s >= r1c && r2s >= r2c && r3s <= r3c)
		func8(r1c, r2c, slots, r3, r1, r2, r1s, r2s, r3s, p, w1, dt, exp, prob_t, p1, p2, p3);
	else func14(r1c, r2c, r3c, slots, r3, r1, r2, r1s, r2s, r3s, p, w1, dt, exp, prob_t, p1, p2, p3);
}

void calcTable3(size_t r3, size_t r1, size_t r1c, size_t r2c, size_t r3c, size_t slots, bool base_d[6][200], long double w1, std::vector<std::vector<std::vector<int>>>& dt, std::vector<std::vector<std::vector<std::vector<long double>>>>& exp, std::vector<std::vector<std::vector<std::vector<long double>>>>& prob_t) {
	for (size_t r2 = 1; r2 < slots; r2++) //(r1,r2,r3)
		for (size_t r3s = 0; r3s < slots - r3; r3s++)
			for (size_t r1s = 0; r1s < slots - r1; r1s++)
				for (size_t r2s = 0; r2s < slots - r2; r2s++)
					for (size_t prob_i = 0; prob_i < 6; prob_i++)
						func15(r1c, r2c, r3c, slots, r3, r1, r2, r1s, r2s, r3s, 0.25 + 0.1 * prob_i, w1, base_d, dt, exp, prob_t, prob_i, prob_i > 0 ? prob_i - 1 : 0, prob_i < 5 ? prob_i + 1 : 5);
}

long double finde2(size_t i, size_t j, size_t coord, size_t r1, size_t r2, size_t r3, size_t r1s, size_t r2s, size_t r3s, std::vector<std::vector<std::vector<std::vector<long double>>>>& prob_t, size_t prob_i) {
	size_t r1p = 0, r2p = 0, r3p = 0; //translate coord to r1p, r2p, r3p
	if (r1 == 0) {
		r1p = r1s;
		if (r2 == 0) {
			r3p = coord + r3s;
			if (r3p == 0)
				return 0;
			else {
				r2p = r2s;
				return r3p * prob_t[prob_i][i][j][r3p - r3s];
			}
		}
		else if (r3 == 0) {
			r3p = r3s;
			if (r3p == 0)
				return 0;
			else {
				r2p = coord + r2s;
				return r3p * prob_t[prob_i][i][j][r2p - r2s];
			}
		}
		else { //r2p is column, r3p is row
			r3p = r3s + coord / (r2 + 1);
			if (r3p == 0)
				return 0;
			else {
				r2p = r2s + coord % (r2 + 1);
				return r3p * prob_t[prob_i][i][j][(r2 + 1) * (r3p - r3s) + r2p - r2s];
			}
		}
	}
	else if (r2 == 0) {
		r2p = r2s;
		if (r3 == 0) {
			r3p = r3s;
			if (r3p == 0)
				return 0;
			else {
				r1p = coord + r1s;
				return r3p * prob_t[prob_i][i][j][r1p - r1s];
			}
		}
		else { //r1p is column, r3p is row
			r3p = r3s + coord / (r1 + 1);
			if (r3p == 0)
				return 0;
			else {
				r1p = r1s + coord % (r1 + 1);
				return r3p * prob_t[prob_i][i][j][(r1 + 1) * (r3p - r3s) + r1p - r1s];
			}
		}
	}
	else if (r3 == 0) { //r2p is column, r1p is row
		r3p = r3s;
		if (r3p == 0)
			return 0;
		else {
			r2p = r2s + coord % (r2 + 1);
			r1p = r1s + coord / (r2 + 1);
			return r3p * prob_t[prob_i][i][j][(r2 + 1) * (r1p - r1s) + r2p - r2s];
		}
	}
	else { //r2p is column, r1p is row, r3p is depth
		size_t s = (r1 + 1) * (r2 + 1);
		r3p = r3s + coord / s;
		if (r3p == 0)
			return 0;
		else {
			size_t t = coord % s;
			r2p = r2s + t % (r2 + 1);
			r1p = r1s + t / (r2 + 1);
			return r3p * prob_t[prob_i][i][j][(r1 + 1) * (r2 + 1) * (r3p - r3s) + (r2 + 1) * (r1p - r1s) + r2p - r2s];
		}
	}
	return 0;
}

long double expr3(size_t i, size_t j, size_t r1, size_t r2, size_t r3, size_t r1s, size_t r2s, size_t r3s, std::vector<std::vector<std::vector<std::vector<long double>>>>& prob_t, size_t prob_i) {
	long double s2 = 0;
	for (size_t z = 0; z < (r1 + 1) * (r2 + 1) * (r3 + 1); z++)
		s2 += finde2(i, j, z, r1, r2, r3, r1s, r2s, r3s, prob_t, prob_i);
	return s2 - r3s;
}

long double finde(size_t i, size_t j, size_t coord, size_t r1, size_t r2, size_t r3, size_t r1s, size_t r2s, size_t r3s, std::vector<std::vector<std::vector<std::vector<long double>>>>& prob_t, size_t prob_i) {
	size_t r1p = 0, r2p = 0, r3p = 0; //translate coord to r1p, r2p, r3p
	if (r1 == 0) {
		r1p = r1s;
		if (r2 == 0) {
			r2p = r2s;
			if (r2p == 0)
				return 0;
			else {
				r3p = coord + r3s;
				return r2p * prob_t[prob_i][i][j][r3p - r3s];
			}
		}
		else if (r3 == 0) {
			r2p = coord + r2s;
			if (r2p == 0)
				return 0;
			else {
				r3p = r3s;
				return r2p * prob_t[prob_i][i][j][r2p - r2s];
			}
		}
		else { //r2p is column, r3p is row
			r2p = r2s + coord % (r2 + 1);
			if (r2p == 0)
				return 0;
			else {
				r3p = r3s + coord / (r2 + 1);
				return r2p * prob_t[prob_i][i][j][(r2 + 1) * (r3p - r3s) + r2p - r2s];
			}
		}
	}
	else if (r2 == 0) {
		r2p = r2s;
		if (r2p == 0)
			return 0;
		else if (r3 == 0) {
			r3p = r3s;
			r1p = coord + r1s;
			return r2p * prob_t[prob_i][i][j][r1p - r1s];
		}
		else { //r1p is column, r3p is row
			r3p = r3s + coord / (r1 + 1);
			r1p = r1s + coord % (r1 + 1);
			return r2p * prob_t[prob_i][i][j][(r1 + 1) * (r3p - r3s) + r1p - r1s];
		}
	}
	else if (r3 == 0) { //r2p is column, r1p is row
		r2p = r2s + coord % (r2 + 1);
		if (r2p == 0)
			return 0;
		else {
			r3p = r3s;
			r1p = r1s + coord / (r2 + 1);
			return r2p * prob_t[prob_i][i][j][(r2 + 1) * (r1p - r1s) + r2p - r2s];
		}
	}
	else { //r2p is column, r1p is row, r3p is depth
		size_t s = (r1 + 1) * (r2 + 1);
		size_t t = coord % s;
		r2p = r2s + t % (r2 + 1);
		if (r2p == 0)
			return 0;
		else {
			r3p = r3s + coord / s;
			r1p = r1s + t / (r2 + 1);
			return r2p * prob_t[prob_i][i][j][(r1 + 1) * (r2 + 1) * r3p + (r2 + 1) * (r1p - r1s) + r2p - r2s];
		}
	}
	return 0;
}

long double expr2(size_t i, size_t j, size_t r1, size_t r2, size_t r3, size_t r1s, size_t r2s, size_t r3s, std::vector<std::vector<std::vector<std::vector<long double>>>>& prob_t, size_t prob_i) {
	long double s2 = 0;
	for (size_t z = 0; z < (r1 + 1) * (r2 + 1) * (r3 + 1); z++)
		s2 += finde(i, j, z, r1, r2, r3, r1s, r2s, r3s, prob_t, prob_i);
	return s2 - r2s;
}

long double findp1(size_t r12p, size_t r4p, size_t i, size_t j, size_t coord, size_t r1, size_t r2, size_t r3, size_t r1s, size_t r2s, size_t r3s, std::vector<std::vector<std::vector<std::vector<long double>>>>& prob_t, size_t prob_i) {
	size_t r1p = 0, r2p = 0, r3p = 0; //translate coord to r1p, r2p, r3p
	if (r1 == 0) {
		r1p = r1s;
		if (r2 == 0) {
			r2p = r2s;
			r3p = coord + r3s;
			if (r1p + r2p >= r12p && r3p <= r4p)
				return prob_t[prob_i][i][j][r3p - r3s];
			return 0;
		}
		else if (r3 == 0) {
			r3p = r3s;
			r2p = coord + r2s;
			if (r1p + r2p >= r12p && r3p <= r4p)
				return prob_t[prob_i][i][j][r2p - r2s];
			return 0;
		}
		else { //r2p is column, r3p is row
			r3p = r3s + coord / (r2 + 1);
			r2p = r2s + coord % (r2 + 1);
			if (r1p + r2p >= r12p && r3p <= r4p)
				return prob_t[prob_i][i][j][(r2 + 1) * (r3p - r3s) + r2p - r2s];
			return 0;
		}
	}
	else if (r2 == 0) {
		r2p = r2s;
		if (r3 == 0) {
			r3p = r3s;
			r1p = coord + r1s;
			if (r1p + r2p >= r12p && r3p <= r4p)
				return prob_t[prob_i][i][j][r1p - r1s];
			return 0;
		}
		else { //r1p is column, r3p is row
			r3p = r3s + coord / (r1 + 1);
			r1p = r1s + coord % (r1 + 1);
			if (r1p + r2p >= r12p && r3p <= r4p)
				return prob_t[prob_i][i][j][(r1 + 1) * (r3p - r3s) + r1p - r1s];
			return 0;
		}
	}
	else if (r3 == 0) {
		r3p = r3s; //r2p is column, r1p is row
		r1p = r1s + coord / (r2 + 1);
		r2p = r2s + coord % (r2 + 1);
		if (r1p + r2p >= r12p && r3p <= r4p)
			return prob_t[prob_i][i][j][(r2 + 1) * (r1p - r1s) + r2p - r2s];
		return 0;
	}
	else { //r2p is column, r1p is row, r3p is depth
		size_t s = (r1 + 1) * (r2 + 1);
		size_t t = coord % s;
		r3p = r3s + coord / s;
		r1p = r1s + t / (r2 + 1);
		r2p = r2s + t % (r2 + 1);
		if (r1p + r2p >= r12p && r3p <= r4p)
			return prob_t[prob_i][i][j][(r1 + 1) * (r2 + 1) * (r3p - r3s) + (r2 + 1) * (r1p - r1s) + r2p - r2s];
		return 0;
	}
	return 0;
}

void func11(size_t r12p, size_t r4p, long double& prob2, size_t i, size_t j, size_t r1, size_t r2, size_t r3, size_t r1s, size_t r2s, size_t r3s, std::vector<std::vector<std::vector<std::vector<long double>>>>& prob_t, int prob_i) {
	prob2 = 0;
	for (size_t z = 0; z < (r1 + 1) * (r2 + 1) * (r3 + 1); z++) //r3p <= r4p and r1p + r2p >= r12p
		prob2 += findp1(r12p, r4p, i, j, z, r1, r2, r3, r1s, r2s, r3s, prob_t, prob_i);
}

long double findp2(size_t r3pc, size_t r1pc, size_t r2pc, size_t i, size_t j, size_t coord, size_t r1, size_t r2, size_t r3, size_t r1s, size_t r2s, size_t r3s, std::vector<std::vector<std::vector<std::vector<long double>>>>& prob_t, size_t prob_i) {
	size_t r1p = 0, r2p = 0, r3p = 0; //translate coord to r1p, r2p, r3p
	if (r1 == 0) {
		r1p = r1s;
		if (r2 == 0) {
			r2p = r2s;
			r3p = coord + r3s;
			if (r3p <= r3pc && r1p >= r1pc && r2p >= r2pc)
				return prob_t[prob_i][i][j][r3p - r3s];
			return 0;
		}
		else if (r3 == 0) {
			r3p = r3s;
			r2p = coord + r2s;
			if (r3p <= r3pc && r1p >= r1pc && r2p >= r2pc)
				return prob_t[prob_i][i][j][r2p - r2s];
			return 0;
		}
		else { //r2p is column, r3p is row
			r3p = r3s + coord / (r2 + 1);
			r2p = r2s + coord % (r2 + 1);
			if (r3p <= r3pc && r1p >= r1pc && r2p >= r2pc)
				return prob_t[prob_i][i][j][(r2 + 1) * (r3p - r3s) + r2p - r2s];
			return 0;
		}
	}
	else if (r2 == 0) {
		r2p = r2s;
		if (r3 == 0) {
			r3p = r3s;
			r1p = coord + r1s;
			if (r3p <= r3pc && r1p >= r1pc && r2p >= r2pc)
				return prob_t[prob_i][i][j][r1p - r1s];
			return 0;
		}
		else { //r1p is column, r3p is row
			r3p = r3s + coord / (r1 + 1);
			r1p = r1s + coord % (r1 + 1);
			if (r3p <= r3pc && r1p >= r1pc && r2p >= r2pc)
				return prob_t[prob_i][i][j][(r1 + 1) * (r3p - r3s) + r1p - r1s];
			return 0;
		}
	}
	else if (r3 == 0) {
		r3p = r3s; //r2p is column, r1p is row
		r1p = r1s + coord / (r2 + 1);
		r2p = r2s + coord % (r2 + 1);
		if (r3p <= r3pc && r1p >= r1pc && r2p >= r2pc)
			return prob_t[prob_i][i][j][(r2 + 1) * (r1p - r1s) + r2p - r2s];
		return 0;
	}
	else { //r2p is column, r1p is row, r3p is depth
		size_t s = (r1 + 1) * (r2 + 1);
		size_t t = coord % s;
		r3p = r3s + coord / s;
		r1p = r1s + t / (r2 + 1);
		r2p = r2s + t % (r2 + 1);
		if (r3p <= r3pc && r1p >= r1pc && r2p >= r2pc)
			return prob_t[prob_i][i][j][(r1 + 1) * (r2 + 1) * (r3p - r3s) + (r2 + 1) * (r1p - r1s) + r2p - r2s];
		return 0;
	}
	return 0;
}

void func12(size_t r3pc, size_t r1pc, size_t r2pc, long double& prob, size_t i, size_t j, size_t r1, size_t r2, size_t r3, size_t r1s, size_t r2s, size_t r3s, std::vector<std::vector<std::vector<std::vector<long double>>>>& prob_t, int prob_i) {
	prob = 0;
	for (size_t z = 0; z < (r1 + 1) * (r2 + 1) * (r3 + 1); z++) //r3p <= r3pc, r1p >= r1pc, r2p >= r2pc
		prob += findp2(r3pc, r1pc, r2pc, i, j, z, r1, r2, r3, r1s, r2s, r3s, prob_t, prob_i);
}

void update_probabilities(long double& prob, long double& prob2, int p, size_t smax, size_t r1p, size_t r2p, size_t r3p, size_t r12p, size_t r4p, size_t s1, size_t r1s, size_t r2s, size_t r3s, size_t row1, size_t row2, size_t row3, std::vector<std::vector<std::vector<std::vector<long double>>>>& prob_t) {
	size_t i = (smax * smax + smax + 1) * s1 - smax * smax * row3 - smax * row1 - row2, j = (row2 + smax - s1) * r1s + r2s;
	func11(r12p, r4p, prob2, i, j, s1 - row1, s1 - row2, s1 - row3, r1s, r2s, r3s, prob_t, (p - 25) / 10);
	func12(r3p, r1p, r2p, prob, i, j, s1 - row1, s1 - row2, s1 - row3, r1s, r2s, r3s, prob_t, (p - 25) / 10);
}

void func13(size_t smax, int& choice, size_t s1, size_t row3, size_t r1s, size_t r2s, size_t r3s, size_t row1, size_t row2, long double& r1e, long double& r2e, long double& r3e, bool p_m, bool sacrifice, long double base_e[6][231], std::vector<std::vector<std::vector<int>>>& dt, std::vector<std::vector<std::vector<std::vector<long double>>>>& exp, std::vector<std::vector<std::vector<std::vector<long double>>>>& prob_t, int prob_i) {
	choice = dt[prob_i][(smax * smax + smax + 1) * s1 - smax * smax * row3 - smax * row1 - row2][(row2 + smax - s1) * r1s + r2s];
	r1e = exp[prob_i][(smax * smax + smax + 1) * s1 - smax * smax * row3 - smax * row1 - row2][(row2 + smax - s1) * r1s + r2s][0];
	if (p_m)
		r2e = expr2((smax * smax + smax + 1) * s1 - smax * smax * row3 - smax * row1 - row2, (row2 + smax - s1) * r1s + r2s, s1 - row1, s1 - row2, s1 - row3, r1s, r2s, r3s, prob_t, prob_i);
	else r2e = exp[prob_i][(smax * smax + smax + 1) * s1 - smax * smax * row3 - smax * row1 - row2][(row2 + smax - s1) * r1s + r2s][1];
	if (sacrifice)
		r3e = expr3((smax * smax + smax + 1) * s1 - smax * smax * row3 - smax * row1 - row2, (row2 + smax - s1) * r1s + r2s, s1 - row1, s1 - row2, s1 - row3, r1s, r2s, r3s, prob_t, prob_i);
	else r3e = base_e[prob_i][23 * s1 - 21 * row3 - row1 - row2];
}

void update_changes(long double& prob, long double& prob2, size_t r1p, size_t r2p, size_t r3p, size_t r12p, size_t r4p, size_t smax, int& p, int& choice, size_t s1, size_t& row3, size_t& r1s, size_t& r2s, size_t& r3s, size_t& row1, size_t& row2, long double& r1e, long double& r2e, long double& r3e, bool p_m, bool sacrifice, long double base_e[6][231], std::vector<std::vector<std::vector<int>>>& dt, std::vector<std::vector<std::vector<std::vector<long double>>>>& exp, std::vector<std::vector<std::vector<std::vector<long double>>>>& prob_t) {
	func13(smax, choice, s1, row3, r1s, r2s, r3s, row1, row2, r1e, r2e, r3e, p_m, sacrifice, base_e, dt, exp, prob_t, (p - 25) / 10);
	if (p_m)
		update_probabilities(prob, prob2, p, smax, r1p, r2p, r3p, r12p, r4p, s1, r1s, r2s, r3s, row1, row2, row3, prob_t);
}
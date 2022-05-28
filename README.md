# Ability Stone Calculator

A GUI Calculator for making optimal decisions for Ability Stones in the game Lost Ark

# Download

The download can be found here: [Ability Stone Calculator Windows 64 bit](https://github.com/DJ0002/AbilityStoneCalculator/releases/tag/v1.5).

## Table of contents

- [Summary](#summary)
- [Method](#method)
- [Tips for compiling](#tips-for-compiling)
- [License](#license)

## Summary

This calculator is different from most other calculators because it always maximizes the expected value for successes in the good engravings, and it allows for high customization based on weights and conditions for the good engravings that cannot be easily represented by pregenerated tables. It also allows you to see the tables for expected values and probabilities based on the applied weights and conditions. The weights range from 0 to 1 where the weight of row 1 + the weight of row 2 = 1. A weight of 0.5 means both rows are equally weighted, and a row with a weight of 1 means that row will be maximized and the other one will be minimized. Probability mode will allow for probability calculations and the display of the actual expected value for the row that is not picked in a tie. The strategy for probability mode is not different from not using it. Probability mode will allow you to enable conditions on row 1 & row 2, which can change the strategy. By enabling conditions, the calculator will maximize the probability of meeting those conditions after maximizing the expected value for successes in good engravings, then it will apply weights after the conditions are met. If the conditions cannot be met, the calculator will aim to for closest conditions that can be met through maximizing the probability. If you are okay with sacrificing successes in good engravings for a higher probability of satisfying the inequalities, then you can enable that option. This option is good when you have no use for stones that don't meet the conditions.

Start off by selecting whether or not you want to enable probability mode, then input the settings and click on the apply settings button, which will perform the calculations to find the optimal strategy. The green area represents the optimal decision determined by the calculator.

## Method

In general, dynamic programming is used to solve the optimization problems. It is done from the bottom-up with tabulation. After the subproblems are solved, their solutions are used to more easily solve the larger problems. For example, the solution for optimizing a problem where there are 2 slots per row can use the solution from a problem where the is 1 slot per row. Click on Example code for more details:

<details>
  <summary>Example code</summary>

```cpp
//for example, can use i = 2, j = 2, p = 0.45, base_e[p1] refers to expected value at rate = 45%, base_e[p2] refers to expected value at rate = 35%,
//and base_e[p3] refers to expected value at rate = 55%, where i = the remaining slots for row 3 and j = the remaining slots for row 1 + row 2
void func1(size_t i, size_t j, long double p, bool base_d[6][200], long double base_e[6][231], size_t p1, size_t p2, size_t p3) {
	long double rg = p * base_e[p2][21 * i + j - 1] + (1 - p) * base_e[p3][21 * i + j - 1]; //expected value of row 3 for choosing row 1 or row 2
	//example gives 0.9181 = 0.45 * the expected value at (rate = 35%, i = 2, j = 1) + 0.55 * the expected value at (rate = 55%, i = 2, j = 1)
	//simplifies to 0.9181 = 0.45 * 0.73 + 0.55 * 1.072 (the 0.73 and 1.072 come from solving their respective subproblems)
	long double rb = p + p * base_e[p2][21 * (i - 1) + j] + (1 - p) * base_e[p3][21 * (i - 1) + j]; //expected value of row 3 for choosing row 3
	//example gives 0.897075 = 0.45 + 0.45 * the expected value at (rate = 35%, i = 1, j = 2) + 0.55 * the expected value at (rate = 55%, i = 1, j = 2)
	//simplifies to 0.897075 = 0.45 + 0.45 * 0.35 + 0.55 * 0.5265 (the 0.35 and 0.5265 come from solving their respective subproblems)
	if (rg < rb) { //choose the decision that minimizes the expected value of row 3
		base_d[p1][20 * (i - 1) + j - 1] = true; //means row 1 or row 2 is chosen
		base_e[p1][21 * i + j] = rg;
	}
	else {
		base_d[p1][20 * (i - 1) + j - 1] = false; //means row 3 is chosen
		base_e[p1][21 * i + j] = rb; //example gives the expected value at (rate = 45%, i = 2, j = 2) = 0.897075
	}
}
```
</details>

The method used for weights can be found in func4, and the method used for conditions on row 1 & row 2 can be found in func10.

## Tips for compiling

There are multiple ways to compile the code, but I have only done so with Visual Studio 2022 using CMake and vcpkg. Cmake can be installed through the Visual Studio Installer and vcpkg can be found [here](https://github.com/microsoft/vcpkg). The packages used are described in [vcpkg.json](https://github.com/DJ0002/AbilityStoneCalculator/blob/main/vcpck.json), and I use x64 libraries for imgui, glad, glfw3, glfw-binding for imgui, and opengl3-binding for imgui. I suppose you could use x86 libraries if you wish to compile for 32 bit. You may want to set the environment variable VCPKG_ROOT to its install location since it is used in [CMakePresets.json](https://github.com/DJ0002/AbilityStoneCalculator/blob/main/CMakePresets.json). If you want to compile for a different operating system, you might need to change the "long double" in the code to something else, but I'm not sure.

## License

Code released under the [MIT License](https://github.com/DJ0002/AbilityStoneCalculator/blob/main/LICENSE).
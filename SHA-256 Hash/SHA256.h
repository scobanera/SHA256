#ifndef SHA_256
#define SHA_256

#include <cstdint>
#include <vector>
#include <string>

// Blocks contain 512 bits (16 words of 32 bits each).
typedef struct block {
	uint32_t words[16] = { 0 };
} Block;

class SHA256 {
public:
	SHA256() {};

	std::string hash(std::string input);

private:
	std::vector<Block> input_message;

	// ======================================================
	// Preprocessing.
	// ======================================================
	void add_pading(std::string& input);

	void parse_message(std::string& input);


	// ======================================================
	// Hashing functions and operators.
	// ======================================================

	// Rotates right a 32 bits word by the given number of positions.
	static uint32_t rotr(uint32_t word, uint32_t positions);

	// For each bit, it returns the value of y or z depending on x,
	//
	// For example, considering the following values at a certain position of every input: x=0, y=1, z=0;
	// the ouput at that position will be the value of 'y' since x=0. If x=1, the value of  'z' would be used, ie 0.
	static uint32_t choose(uint32_t x, uint32_t y, uint32_t z);

	// For each bit, it returns the majority of x, y, and z.
	//
	// For example, considering the following values at a certain position of every input: x=0, y=1, z=0;
	// since there are two 0s and one 1, the output at that position would be 0.
	static uint32_t majority(uint32_t a, uint32_t b, uint32_t c);

	// Sigma 0: operation as defined in SHA standard.
	static uint32_t sig0(uint32_t x);

	// Sigma 1: operation as defined in SHA standard.
	static uint32_t sig1(uint32_t x);


	// ======================================================
	// Constants.
	// ======================================================
	static constexpr uint32_t initial_hash_value[] = {
		0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a,
		0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19 };

	static constexpr uint32_t round_constant[] = { 1, 2, 3 };
};

#endif // !SHA256
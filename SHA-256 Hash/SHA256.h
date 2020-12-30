#ifndef SHA_256
#define SHA_256

#include <cstdint>
#include <vector>
#include <string>

// Block of 512 bits (16 words of 32 bits each).
typedef struct block {
	uint32_t words[16] = { 0 };
} Block;

class SHA256 {
public:
	SHA256() {};

	std::string hash(std::string input);

private:
	std::vector<Block> message_blocks;

	// ======================================================
	// Preprocessing.
	// ======================================================
	void add_pading(std::string& input);

	void parse_message(std::string& input);

	// ======================================================
	// Hash computation.
	// ======================================================
	std::string compute_hash();

	// ======================================================
	// Hashing functions and operators.
	// ======================================================

	// Rotates right a 32 bits word by the given number of positions.
	static uint32_t rotr(uint32_t word, uint32_t positions);

	// For each bit, it returns the value of y or z depending on x,
	//
	// For example, considering the following values at a certain position of every input: x=0, y=1, z=0;
	// the ouput at that position will be the value of 'z' since x=0. If x=1, the value of  'y' would be used, ie 0.
	static uint32_t choose(uint32_t x, uint32_t y, uint32_t z);

	// For each bit, it returns the majority of x, y, and z.
	//
	// For example, considering the following values at a certain position of every input: x=0, y=1, z=0;
	// since there are two 0s and one 1, the output at that position would be 0.
	static uint32_t majority(uint32_t a, uint32_t b, uint32_t c);

	// Uppercase Sigma 0: operation as defined in SHA standard.
	static uint32_t upperSigma0(uint32_t x);

	// Uppercase Sigma 1: operation as defined in SHA standard.
	static uint32_t upperSigma1(uint32_t x);

	// Lowercase Sigma 1: operation as defined in SHA standard.
	static uint32_t lowerSigma0(uint32_t x);

	// Lowercase Sigma 1: operation as defined in SHA standard.
	static uint32_t lowerSigma1(uint32_t x);


	// ======================================================
	// Constants.
	// ======================================================
	static constexpr uint32_t initial_hash_value[] = {
		0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a,
		0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19 };

	static constexpr uint32_t round_constant[] = {
		0x428a2f98,0x71374491,0xb5c0fbcf,0xe9b5dba5,
		0x3956c25b,0x59f111f1,0x923f82a4,0xab1c5ed5,
		0xd807aa98,0x12835b01,0x243185be,0x550c7dc3,
		0x72be5d74,0x80deb1fe,0x9bdc06a7,0xc19bf174,
		0xe49b69c1,0xefbe4786,0x0fc19dc6,0x240ca1cc,
		0x2de92c6f,0x4a7484aa,0x5cb0a9dc,0x76f988da,
		0x983e5152,0xa831c66d,0xb00327c8,0xbf597fc7,
		0xc6e00bf3,0xd5a79147,0x06ca6351,0x14292967,
		0x27b70a85,0x2e1b2138,0x4d2c6dfc,0x53380d13,
		0x650a7354,0x766a0abb,0x81c2c92e,0x92722c85,
		0xa2bfe8a1,0xa81a664b,0xc24b8b70,0xc76c51a3,
		0xd192e819,0xd6990624,0xf40e3585,0x106aa070,
		0x19a4c116,0x1e376c08,0x2748774c,0x34b0bcb5,
		0x391c0cb3,0x4ed8aa4a,0x5b9cca4f,0x682e6ff3,
		0x748f82ee,0x78a5636f,0x84c87814,0x8cc70208,
		0x90befffa,0xa4506ceb,0xbef9a3f7,0xc67178f2
	};
};

#endif // !SHA256
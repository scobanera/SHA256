#include "SHA256.h"
#include <iostream>
#include <string>

using std::cout;
using std::endl;

void print_binary(uint32_t value) {
	for (int8_t pos = 31; pos >= 0; pos--) {
		uint32_t mask = 1 << pos;
		
		if (value & mask) {
			cout << "1";
		}
		else {
			cout << "0";
		}

		if (pos % 8 == 0)
			cout << " ";
	}
	cout << endl;
}

void print_block(Block block) {
	cout << "Printing block:\n";
	for (int word = 0; word < 16; word++) {
		cout << "Word " << word << ": ";
		print_binary(block.words[word]);
	}
	cout << endl;
}

void SHA256::add_pading(std::string &input) {
	uint64_t message_bits = input.size() * 8;
	uint64_t bits_last_block = message_bits % 512;

	// The last block contains: [message, 1-bit delimiter, padding zeros, and 64 bits for message length]. 
	// If message size is greater than 447 bits there isn't enough space for the message length and delimiter,
	// therefore more padding needs to be added ti create a new block.
	int16_t padding_zeros;
	if (bits_last_block > 447) {
		padding_zeros = 1024 - bits_last_block - 65;
	}
	else {
		padding_zeros = 512 - bits_last_block - 65;
	}

	// Append delimiter and 7 zeros (there will always be at least 7 zeros).
	input.push_back(0x80);

	// Append padding.
	for (int16_t i = padding_zeros - 7; i > 0; i -= 8) {
		input.push_back(0);
	}

	// Append message length.
	for (int8_t shift = 56; shift >= 0; shift -= 8) {
		input.push_back((message_bits >> shift) & 0xFF);
	}
}

void SHA256::parse_message(std::string& input) {
	Block current_block;
	uint32_t word = 0;
	uint8_t processed_characters = 0;
	uint8_t processed_words = 0;

	for (const uint8_t& character : input) {
		word <<= 8;
		word += character;

		// Every 4 processed characters we have a new 32-bits word.
		if (++processed_characters == 4) {
			current_block.words[processed_words++] = word;
			word = processed_characters = 0;

			// Every 16 processed words we have a new 512-bits block.
			if (processed_words == 16) {
				input_message.push_back(current_block);
				processed_words = 0;
				current_block = {};
			}
		}
	}

	for (const auto& block : input_message) {
		print_block(block);
	}
}

std::string SHA256::hash(std::string input) {
	// Preprocessing stage.
	add_pading(input);
	parse_message(input);

	// Hash computation.
	// Here will be the hash computation.

	return input.append("Here will go the resulting hash.");
}



#include <iostream>
#include <stdlib.h>
#include <assert.h>
#include "bitstring.h"

Bitstring::Bitstring(unsigned int bits) {
	this->bits = bits;

	this->len = bits/64;
	if (bits % 64 > 0) {
		this->len++;
	}

	this->data = (int64_t *) malloc(sizeof(int64_t) * this->len);

	for (int i=0; i<this->len; i++) {
		this->data[i] = ((int64_t)arc4random() << 32) | arc4random();
	}

	int last = bits % 64;
	if (last > 0) {
		this->data[this->len-1] &= ~((int64_t)0xFFFFFFFFFFFFFFFF << last);
	}
}

Bitstring::~Bitstring() {
	free(this->data);
}

unsigned int Bitstring::get(unsigned int bit) const {
	assert(bit <= this->bits);
	unsigned int offset = bit / 64;
	unsigned int idx = bit % 64;
	return (data[offset] & ((int64_t)1<<idx) ? 1 : 0);
}

void Bitstring::set(unsigned int bit, unsigned int value) {
	unsigned int offset = bit / 64;
	unsigned int idx = bit % 64;
	if (value == 0) {
		data[offset] &= ~((int64_t)1<<idx);
	} else {
		data[offset] |= ((int64_t)1<<idx);
	}
}

int Bitstring::distance(const Bitstring *bs) const {
	if (this->bits != bs->bits) {
		return -1;
	}

	uint64_t a;
	int dist = 0;
	for(int i=0; i<this->len; i++) {
		a = this->data[i] ^ bs->data[i];
		while(a) {
			if (a%2) {
				dist++;
			}
			a >>= 1;
		}
	}
	return dist;
}

std::string Bitstring::str() const {
	char str[this->bits+1];
	for(int i=0; i<this->bits; i++) {
		str[i] = this->get(i) ? '1' : '0';
	}
	str[this->bits] = '\0';
	return std::string(str);
}


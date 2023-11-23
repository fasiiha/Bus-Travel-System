#include <iostream>
#include <ctime>
#include <string>
#include <functional>
#include <cstdint>
#include <vector>
#include <chrono>
#include <fstream>
#include "SHA256.cpp"

using namespace std;

class Block{
	public: 
		string prevhash;	//stores previous block hash
		uint32_t  index; //stores block number
		time_t currTime ;	//stores time
		string hash;	//stores current block hash
		string data;	//stores data
		int64_t nonce;
		
	Block(uint32_t indexIn, const string & dataIn) : index(indexIn), data(dataIn) {
		this -> nonce = -1;
		this -> currTime = time(nullptr);
	}

	uint32_t getIndex() const {
		return this-> index;
	}
	
	time_t getTime() const {
		return this-> currTime;
	}
	
	string getHash() const {
		return this -> hash;
	}
	
	void createGenesis() {
		this -> nonce = -1;
		this -> currTime = time(nullptr);
		this -> index = 0;
		this -> data = "";
		this -> hash = "0000000000000000000000000000000000000000000000000000000000000000";
	}

	const string calculateHash()  {
		string ss = to_string(index) + to_string(currTime) + data + to_string(nonce) + prevhash + " ";
		return sha256(ss);
	}
	
	void DOMine(uint32_t difficulty) {
		char * cstr = new char[difficulty + 1];
		for (uint32_t i = 0; i < difficulty; ++i) {
			cstr[i] = '0';
		}
		cstr[difficulty] = '\0';
		string str(cstr);
	cout << "str(cstr): " << str << " Difficulty: " << difficulty << " cstr: " << cstr << endl;
		do {
			cout << "this-> hash.substr(0, difficulty): " <<  this-> hash.substr(0, difficulty) << endl;
			this-> nonce++;
			this-> hash = calculateHash();
		} while (!str.compare(this-> hash.substr(0, difficulty)));
	
		cout << "Block mined: " << this-> hash << endl;
	}
};

class BlockChain{
	public:
		uint32_t difficulty;
		vector<Block> chain;
	
	BlockChain(){
		this -> difficulty = 10;
	}
	
	void AddGenesis() {
		Block genesis(0," ");
		genesis.createGenesis();
		this-> chain.emplace_back(genesis);
	}
	
	void AddBlock(Block newBlock) {
		newBlock.prevhash = getLastBlock().getHash();
		newBlock.DOMine(this-> difficulty);
		this-> chain.push_back(newBlock);
	}
	
	const Block getLastBlock() const {
		return this-> chain.back();
	}
	
	const uint32_t getChainSize() const {
		return this-> chain.size();
	}
	
	void printBlocks() {
		cout << endl << "All blocks:" << endl;
		for (const auto &block : this-> chain) {
			cout << "Index: " << block.getIndex()
				 << " Time: " << block.getTime()
				 << " Hash: " << block.getHash() << endl;
//			cout	 << " PrevHash:: " << block.prevhash << endl;
		}
		cout << endl;
	}
};

int main(){
	BlockChain bChain = BlockChain();
	
	cout << "Genesis..." << endl;
	bChain.AddGenesis();

	cout << "Mining block 1..." << endl;
	bChain.AddBlock(Block(1, "Fasiha"));

	cout << "Mining block 2..." << endl;
	bChain.AddBlock(Block(2, "amnasmn"));

	cout << "Mining block 3..." << endl;
	bChain.AddBlock(Block(3, "asdnsambda"));

	bChain.printBlocks();
	
	return 0;
}
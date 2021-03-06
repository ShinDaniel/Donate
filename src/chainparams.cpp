// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2017 The PIVX developers
// Copyright (c) 2018 The donate developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "libzerocoin/Params.h"
#include "chainparams.h"
#include "random.h"
#include "util.h"
#include "utilstrencodings.h"

#include <assert.h>

#include <boost/assign/list_of.hpp>

using namespace std;
using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

/**
 * Main network
 */

//! Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress>& vSeedsOut, const SeedSpec6* data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7 * 24 * 60 * 60;
    for (unsigned int i = 0; i < count; i++) {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

//   What makes a good checkpoint block?
// + Is surrounded by blocks with reasonable timestamps
//   (no blocks before with a timestamp after, none after with
//    timestamp before)
// + Contains no strange transactions
static Checkpoints::MapCheckpoints mapCheckpoints =
        boost::assign::map_list_of
                // donateDevs - RELEASE CHANGE - Checkpoints, timestamp of last checkpoint, total nr. of transactions
                (       0, uint256("00000c4ffa2c7934a53d4e8383af778bd0c961341ee22d837e51c1f53b56fc18"))
                (       500, uint256("000000002701c3dd7c19922b439f46251bf833a17399f2ed69163a770133eb50"))
                (       1000, uint256("00000008cbfeecba65fb88418589b005ac61a547e476a94bb01c3a631eda6c0f"))
                (       1500, uint256("0000001019b4b2253074058565f8f9e31c0b94318bb0d52239f3edcddd48ec72"))
                (       2000, uint256("00000011364c5d5c1ea354aadf88d1017c08bd4c0f472e1588c45b591a67061a"))
                (       2500, uint256("000000002ef29cba83fe8952038110b1c3d44e7a6f91bf3ff62716bccce10401"))
                (       5000, uint256("0000000004171709af65c3576f9f3b2347b9a78f35466a4c0e67f4b58083a593"))
                (       8000, uint256("00000000019a2a9feb99a9ed49e84ab5108436cb45e80b1115f2e4334b46d306"))
                (       8001, uint256("5f85b090993ab18290c2d24cbdeec4c5eb0732d0bf9c87efd92f59aa8e552bfe"))
                (       10000, uint256("7de29e948c54311b863c0d56eeab828f207dc33f77fe5906ae5d0b6411d84283"))
                (       15000, uint256("3c86cc64a9fa649d75b32d588485cc127594fd107fca91f8dab0c0442ba3ef7e"))
                (       20000, uint256("e045aee2480f2a5be795035cb3c380f16d504c1690ca50694df5f9ff3752e62d"))
                (       25000, uint256("d6a4a25ed9c6448fd4cf16120ce1a773ede4734e6c14fc2829e40550eb4534c7"))
                (       30000, uint256("b99cb0b836152bd3fc52565e0e79162ac125e57d6641534a0e070fd76c8e036e"))
                (       40000, uint256("e36b01f14b1c7761eeef3c1b21b5292261196f42e76d08d23c3a361882a14946"))
                (       50000, uint256("d79ad638259f3837ab25769130a518238ef9b6b20653d98df96e602fd1c8ee98"))
                (       60000, uint256("fc525d56bb1a724b8ac52f7b8b91e1bbc60fe541e37ed2743f99cfe5d1770e4c"))
                (       70000, uint256("d48e8b10fcf64eaa3edc5f873370be16c86ab639f4cd13df2fab9c9e8a1d0742"))
                (       80000, uint256("49fb6da4cbc4e834312985bfa44b08537a4c4573bbca6a37626b46e66ea246d6"))
                (       90000, uint256("4035ca075e6a5759d15edd9494fd925da415baec9058dd04664b119f7a319fe9"))
                (       100000, uint256("0d593545ea7f76f3012d131da70b449218b24a0eaf88db661149b08589f8b925"))
                ;

static const Checkpoints::CCheckpointData data = {
        &mapCheckpoints,
        1549617274, // * UNIX timestamp of last checkpoint block
        194131,       // * total number of transactions between genesis and last checkpoint
                    //   (the tx=... number in the SetBestChain debug.log lines)
        2000        // * estimated number of transactions per day after checkpoint
};

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
        boost::assign::map_list_of
                (       0, uint256("0000044b0d37b6c646a10832f3382f0ef24fbb0ca70c3781def579dfb1593c64"))
        ;        // First PoW block
static const Checkpoints::CCheckpointData dataTestnet = {
        &mapCheckpointsTestnet,
        1543482352,
        1,
        300};

static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
    boost::assign::map_list_of(0, uint256("0x"));
static const Checkpoints::CCheckpointData dataRegtest = {
    &mapCheckpointsRegtest,
    1543482352,
    0,
    100};

libzerocoin::ZerocoinParams* CChainParams::Zerocoin_Params() const
{
    assert(this);
    static CBigNum bnTrustedModulus(zerocoinModulus);
    static libzerocoin::ZerocoinParams ZCParams = libzerocoin::ZerocoinParams(bnTrustedModulus);

    return &ZCParams;
}

class CMainParams : public CChainParams
{
public:
    CMainParams()
    {
        networkID = CBaseChainParams::MAIN;
        strNetworkID = "main";
        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0] = 0xa5;
        pchMessageStart[1] = 0x6b;
        pchMessageStart[2] = 0xc7;
        pchMessageStart[3] = 0x8d;
        vAlertPubKey = ParseHex("041fc0106697e3a3770768d645948cae60c5bf30ebb73e5de4550ef410969890e15bf24ff9037ac5a048d1da71e6239e7e32ecb1335d1fa7ec2fc896ed1e424905");
        nDefaultPort = 39811;
        bnProofOfWorkLimit = ~uint256(0) >> 20; // donate starting difficulty is 1 / 2^12
        nSubsidyHalvingInterval = 210000;       // Halving interval
        nMaxReorganizationDepth = 100;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 0;                      // Obsolete (**TODO**)
        nTargetTimespan = 1 * 60;               // donate: 1 minute
        nTargetSpacing = 1 * 60;                // donate: 1 minutes
        nMaturity = 25;                         // Block maturity
        nMasternodeCountDrift = 20;
        nMaxMoneyOut = 60000000000 * COIN;        // Large number effectively unlimited. Will deprecate TODO
        nMasternodeCollateral = 10000000;          // Masternode Collateral requirement
        /** Height or Time Based Activations **/
        nLastPOWBlock = 8000;                  //
        nModifierUpdateBlock = 1100;            // Modify block on height
        nZerocoinStartHeight = 9900000;         // DISABLED FOR NOW TODO Zerocoin start height
        nZerocoinStartTime = 1609459200;        // Jan 1, 2021 00:00:00 AM (GMT)
        nBlockEnforceSerialRange = 1;           // Enforce serial range starting this block
        nBlockRecalculateAccumulators = 10000000; // Trigger a recalculation of accumulators
        nBlockFirstFraudulent = 1110;           // 1110; //First block that bad serials emerged (currently we do not have any) *** TODO ***
        nBlockLastGoodCheckpoint = 1001;        // Last valid accumulator checkpoint (currently we do not have any) *** TODO ***
        nBlockEnforceInvalidUTXO = 1110;        // Start enforcing the invalid UTXO's

        /**
         * Build the genesis block. Note that the output of the genesis coinbase cannot
         * be spent as it did not originally exist in the database.
         *
         * CBlock(hash=00000ffd590b14, ver=1, hashPrevBlock=00000000000000, hashMerkleRoot=e0028e, nTime=1390095618, nBits=1e0ffff0, nNonce=28917698, vtx=1)
         *   CTransaction(hash=e0028e, ver=1, vin.size=1, vout.size=1, nLockTime=0)
         *     CTxIn(COutPoint(000000, -1), coinbase 04ffff001d01044c5957697265642030392f4a616e2f3230313420546865204772616e64204578706572696d656e7420476f6573204c6976653a204f76657273746f636b2e636f6d204973204e6f7720416363657074696e6720426974636f696e73)
         *     CTxOut(nValue=50.00000000, scriptPubKey=0xA9037BAC7050C479B121CF)
         *   vMerkleTree: e0028e
         */
        const char* pszTimestamp = "South Korea beat Germany 2:0 at the World Cup in Russia on June 17, 2018.";
        CMutableTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue = 0 * COIN;
        txNew.vout[0].scriptPubKey = CScript() << ParseHex("0413b080dec0ce4595f60fc66380ee24ca8ca8fca75419828066c92efe6382e88f4d2e46c39bfcb14c298670300a9b423138a4cc9be5c423c1910f8e3c86b23f14") << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 3;
        genesis.nTime = 1543482352;  // GMT: 2018-11-29 T18:06:00.000Z
        genesis.nBits = 0x1e0ffff0;
        genesis.nNonce = 111353830;

        hashGenesisBlock = genesis.GetHash();
        if(genesis.GetHash() != uint256("00000c4ffa2c7934a53d4e8383af778bd0c961341ee22d837e51c1f53b56fc18"))
        {
            printf("Searching for genesis block...\n");
            uint256 hashTarget = CBigNum().SetCompact(genesis.nBits).getuint256();
            while(uint256(genesis.GetHash()) > hashTarget)
            {
                ++genesis.nNonce;
                if (genesis.nNonce == 0)
                {
                    printf("NONCE WRAPPED, incrementing time");
                    std::cout << std::string("NONCE WRAPPED, incrementing time:\n");
                    ++genesis.nTime;
                }
                if (genesis.nNonce % 10000 == 0)
                {
                    printf("Mainnet: nonce %08u: hash = %s \n", genesis.nNonce, genesis.GetHash().ToString().c_str());
                }
            }
            printf("block.nTime = %u \n", genesis.nTime);
            printf("block.nNonce = %u \n", genesis.nNonce);
            printf("block.GetHash = %s\n", genesis.GetHash().ToString().c_str());
            printf("block.hashMerkleRoot = %s\n", genesis.hashMerkleRoot.ToString().c_str());
        }
        assert(hashGenesisBlock == uint256("00000c4ffa2c7934a53d4e8383af778bd0c961341ee22d837e51c1f53b56fc18"));
        assert(genesis.hashMerkleRoot == uint256("d28e80591f704bd5e22d515ff26d6fe1e2bb01b333ac3fe11f05ea11aecf76e9"));

        vSeeds.clear();
        //vSeeds.push_back(CDNSSeedData("dnsseed.donate.pro"    , "dnsseed.donate.pro"    ));
        //vSeeds.push_back(CDNSSeedData("dnsseed.masternodes.pro", "dnsseed.masternodes.pro"));
        //vSeeds.push_back(CDNSSeedData("45.32.137.248", "45.32.137.248"));
        //vSeeds.push_back(CDNSSeedData("45.76.127.223", "45.76.127.223"));
        //vSeeds.push_back(CDNSSeedData("45.77.226.195", "45.77.226.195"));
        //vSeeds.push_back(CDNSSeedData("207.148.0.5", "207.148.0.5"));
        //vSeeds.push_back(CDNSSeedData("45.77.242.133", "45.77.242.133"));
        vSeeds.push_back(CDNSSeedData("117.52.87.33", "117.52.87.33"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 63); // addresses start with S
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 55); // scripts start with P
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 53); // private key start with N
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x02)(0x2D)(0x25)(0x33).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x02)(0x21)(0x31)(0x2B).convert_to_container<std::vector<unsigned char> >();
        // 	BIP44 coin type is from https://github.com/satoshilabs/slips/blob/master/slip-0044.md
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0x77).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = false;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fSkipProofOfWorkCheck = false;
        fTestnetToBeDeprecatedFieldRPC = false;
        fHeadersFirstSyncingActive = false;

        nPoolMaxTransactions = 3;
        strSporkKey = "044a30edfb288d8973761070dc8b456d429c7b8872d475a837e09e71d3b710c08055852a50de199ee04c0643ebb4bce1c52a27c63cec13c62cf2f84eda00d8a3a6";
        strObfuscationPoolDummyAddress = "SNw1Qz26zMtELShYCLmkE4VXE4ELyD7i8u";
        nStartMasternodePayments = 1543482352; // GMT: 2018-11-29 T18:06:00.000Z

        /** Zerocoin */
        zerocoinModulus = "25195908475657893494027183240048398571429282126204032027777137836043662020707595556264018525880784"
            "4069182906412495150821892985591491761845028084891200728449926873928072877767359714183472702618963750149718246911"
            "6507761337985909570009733045974880842840179742910064245869181719511874612151517265463228221686998754918242243363"
            "7259085141865462043576798423387184774447920739934236584823824281198163815010674810451660377306056201619676256133"
            "8441436038339044149526344321901146575444541784240209246165157233507787077498171257724679629263863563732899121548"
            "31438167899885040445364023527381951378636564391212010397122822120720357";
        nMaxZerocoinSpendsPerTransaction = 7; // Assume about 20kb each
        nMinZerocoinMintFee = 1 * CENT; //high fee required for zerocoin mints
        nMintRequiredConfirmations = 20; //the maximum amount of confirmations until accumulated in 19
        nRequiredAccumulation = 1;
        nDefaultSecurityLevel = 100; //full security level for accumulators
        nZerocoinHeaderVersion = 4; //Block headers must be this version once zerocoin is active
        nBudget_Fee_Confirmations = 6; // Number of confirmations for the finalization fee
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return data;
    }
};

static CMainParams mainParams;

/**
 * Testnet (v3)
 */
class CTestNetParams : public CMainParams
{
public:
    CTestNetParams()
    {
        networkID = CBaseChainParams::TESTNET;
        strNetworkID = "test";
        pchMessageStart[0] = 0xc4;
        pchMessageStart[1] = 0x5d;
        pchMessageStart[2] = 0xe6;
        pchMessageStart[3] = 0xf7;
        vAlertPubKey = ParseHex("048e6fa939c7023cf338182fc983f7c2743161d000407bc48c0e6db65021f79e0985294386d120fe7f9882896dff519ffbdf965be8ecf31a520996837d0024a5d4");
        nDefaultPort = 39813;
        nEnforceBlockUpgradeMajority = 51;
        nRejectBlockOutdatedMajority = 75;
        nToCheckBlockUpgradeMajority = 100;
        nMinerThreads = 0;
        nTargetTimespan = 1 * 60; // donate: 1 day
        nTargetSpacing = 1 * 60;  // donate: 2 minutes
        nLastPOWBlock = 150;
        nMaturity = 15;
        nMasternodeCountDrift = 4;
        nModifierUpdateBlock = 1; //approx Mon, 17 Apr 2017 04:00:00 GMT
        nMaxMoneyOut = 1000000000 * COIN;
        nZerocoinStartHeight = 250;
        nZerocoinStartTime = 1546300800; // Saturday, Jan 1, 2019 00:00:00 AM (GMT)
        nBlockEnforceSerialRange = 1; //Enforce serial range starting this block
        nBlockRecalculateAccumulators = 1500; //Trigger a recalculation of accumulators
        nBlockFirstFraudulent = 891737; //First block that bad serials emerged (currently we do not have any) *** TODO ***
        nBlockLastGoodCheckpoint = 1001; //Last valid accumulator checkpoint (currently we do not have any) *** TODO ***
        nBlockEnforceInvalidUTXO = 1600; //Start enforcing the invalid UTXO's

        //! Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nTime = 1546074568;  // GMT: 2018-12-29 T18:10:00.000Z
        genesis.nNonce = 83740810;

        hashGenesisBlock = genesis.GetHash();
        if(genesis.GetHash() != uint256("0000044b0d37b6c646a10832f3382f0ef24fbb0ca70c3781def579dfb1593c64"))
        {
            printf("Searching for genesis block...\n");
            uint256 hashTarget = CBigNum().SetCompact(genesis.nBits).getuint256();
            while(uint256(genesis.GetHash()) > hashTarget)
            {
                ++genesis.nNonce;
                if (genesis.nNonce == 0)
                {
                    printf("NONCE WRAPPED, incrementing time");
                    std::cout << std::string("NONCE WRAPPED, incrementing time:\n");
                    ++genesis.nTime;
                }
                if (genesis.nNonce % 10000 == 0)
                {
                    printf("Testnet: nonce %08u: hash = %s \n", genesis.nNonce, genesis.GetHash().ToString().c_str());
                }
            }
            printf("block.nTime = %u \n", genesis.nTime);
            printf("block.nNonce = %u \n", genesis.nNonce);
            printf("block.GetHash = %s\n", genesis.GetHash().ToString().c_str());
            printf("block.hashMerkleRoot = %s\n", genesis.hashMerkleRoot.ToString().c_str());
        }
        assert(hashGenesisBlock == uint256("0000044b0d37b6c646a10832f3382f0ef24fbb0ca70c3781def579dfb1593c64"));

        vFixedSeeds.clear();
        vSeeds.clear();
        //vSeeds.push_back(CDNSSeedData("149.28.82.70", "149.28.82.70"));
        //vSeeds.push_back(CDNSSeedData("149.28.248.6", "149.28.248.6"));
        //vSeeds.push_back(CDNSSeedData("144.202.17.23", "144.202.17.23"));
        vSeeds.push_back(CDNSSeedData("117.52.87.33", "117.52.87.33"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 125); // Testnet donate addresses start with 's'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 117);  // Testnet donate script addresses start with 'p'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 112);     // Testnet private keys start with 'n'
        // Testnet donate BIP32 pubkeys start with 'DRKV'
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x3a)(0x80)(0x61)(0xa0).convert_to_container<std::vector<unsigned char> >();
        // Testnet donate BIP32 prvkeys start with 'DRKP'
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x3a)(0x80)(0x58)(0x37).convert_to_container<std::vector<unsigned char> >();
        // Testnet donate BIP44 coin type is '1' (All coin's testnet default)
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0x01).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = true;

        // we enable for test purpose low dif mining on main
        nPoolMaxTransactions = 2;
        strSporkKey = "0435f3871b668f1abba8b8ed01a881e3b211464cd8609a6c59adc92a9aa8c333a03a16ae17bcb583e8aa601d3cb6d662513a7c6d668ec88a397d0b1d22ae9c3954";
        strObfuscationPoolDummyAddress = "sMPUBzcsHZawA32XYYDF9FHQp6icv492CV";
        nStartMasternodePayments = 1529903701;  // GMT: 2018-06-09T00:00:00Z
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataTestnet;
    }
};
static CTestNetParams testNetParams;

/**
 * Regression test
 */
class CRegTestParams : public CTestNetParams
{
public:
    CRegTestParams()
    {
        networkID = CBaseChainParams::REGTEST;
        strNetworkID = "regtest";
        strNetworkID = "regtest";
        pchMessageStart[0] = 0x5a;
        pchMessageStart[1] = 0xe5;
        pchMessageStart[2] = 0x9c;
        pchMessageStart[3] = 0x3d;
        nSubsidyHalvingInterval = 150;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 1;
        nTargetTimespan = 24 * 60 * 60; // donate: 1 day
        nTargetSpacing = 1 * 60;        // donate: 1 minutes
        bnProofOfWorkLimit = ~uint256(0) >> 1;
        genesis.nTime = 1543482352;  // GMT: 2018-11-29 T18:06:02.000Z
        genesis.nBits = 0x207fffff;
        genesis.nNonce = 574757;

        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 39815;
        if(genesis.GetHash() != uint256("2b2d8c260e1eb61d2e81fb8a652bd2465985ab3ef91273ab7e0698db849c16aa"))
        {
            printf("Searching for genesis block...\n");
            uint256 hashTarget = CBigNum().SetCompact(genesis.nBits).getuint256();
            while(uint256(genesis.GetHash()) > hashTarget)
            {
                ++genesis.nNonce;
                if (genesis.nNonce == 0)
                {
                    printf("NONCE WRAPPED, incrementing time");
                    std::cout << std::string("NONCE WRAPPED, incrementing time:\n");
                    ++genesis.nTime;
                }
                if (genesis.nNonce % 10000 == 0)
                {
                    printf("RegTest: nonce %08u: hash = %s \n", genesis.nNonce, genesis.GetHash().ToString().c_str());
                }
            }
            printf("block.nTime = %u \n", genesis.nTime);
            printf("block.nNonce = %u \n", genesis.nNonce);
            printf("block.GetHash = %s\n", genesis.GetHash().ToString().c_str());
            printf("block.hashMerkleRoot = %s\n", genesis.hashMerkleRoot.ToString().c_str());
        }

        assert(hashGenesisBlock == uint256("2b2d8c260e1eb61d2e81fb8a652bd2465985ab3ef91273ab7e0698db849c16aa"));

        vFixedSeeds.clear(); //! Testnet mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Testnet mode doesn't have any DNS seeds.

        fMiningRequiresPeers = false;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;
        fTestnetToBeDeprecatedFieldRPC = false;
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataRegtest;
    }
};
static CRegTestParams regTestParams;

/**
 * Unit test
 */
class CUnitTestParams : public CMainParams, public CModifiableParams
{
public:
    CUnitTestParams()
    {
        networkID = CBaseChainParams::UNITTEST;
        strNetworkID = "unittest";
        nDefaultPort = 51478;
        vFixedSeeds.clear(); //! Unit test mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Unit test mode doesn't have any DNS seeds.

        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        fAllowMinDifficultyBlocks = false;
        fMineBlocksOnDemand = true;
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        // UnitTest share the same checkpoints as MAIN
        return data;
    }

    //! Published setters to allow changing values in unit test cases
    virtual void setSubsidyHalvingInterval(int anSubsidyHalvingInterval) { nSubsidyHalvingInterval = anSubsidyHalvingInterval; }
    virtual void setEnforceBlockUpgradeMajority(int anEnforceBlockUpgradeMajority) { nEnforceBlockUpgradeMajority = anEnforceBlockUpgradeMajority; }
    virtual void setRejectBlockOutdatedMajority(int anRejectBlockOutdatedMajority) { nRejectBlockOutdatedMajority = anRejectBlockOutdatedMajority; }
    virtual void setToCheckBlockUpgradeMajority(int anToCheckBlockUpgradeMajority) { nToCheckBlockUpgradeMajority = anToCheckBlockUpgradeMajority; }
    virtual void setDefaultConsistencyChecks(bool afDefaultConsistencyChecks) { fDefaultConsistencyChecks = afDefaultConsistencyChecks; }
    virtual void setAllowMinDifficultyBlocks(bool afAllowMinDifficultyBlocks) { fAllowMinDifficultyBlocks = afAllowMinDifficultyBlocks; }
    virtual void setSkipProofOfWorkCheck(bool afSkipProofOfWorkCheck) { fSkipProofOfWorkCheck = afSkipProofOfWorkCheck; }
};
static CUnitTestParams unitTestParams;


static CChainParams* pCurrentParams = 0;

CModifiableParams* ModifiableParams()
{
    assert(pCurrentParams);
    assert(pCurrentParams == &unitTestParams);
    return (CModifiableParams*)&unitTestParams;
}

const CChainParams& Params()
{
    assert(pCurrentParams);
    return *pCurrentParams;
}

CChainParams& Params(CBaseChainParams::Network network)
{
    switch (network) {
    case CBaseChainParams::MAIN:
        return mainParams;
    case CBaseChainParams::TESTNET:
        return testNetParams;
    case CBaseChainParams::REGTEST:
        return regTestParams;
    case CBaseChainParams::UNITTEST:
        return unitTestParams;
    default:
        assert(false && "Unimplemented network");
        return mainParams;
    }
}

void SelectParams(CBaseChainParams::Network network)
{
    SelectBaseParams(network);
    pCurrentParams = &Params(network);
}

bool SelectParamsFromCommandLine()
{
    CBaseChainParams::Network network = NetworkIdFromCommandLine();
    if (network == CBaseChainParams::MAX_NETWORK_TYPES)
        return false;

    SelectParams(network);
    return true;
}

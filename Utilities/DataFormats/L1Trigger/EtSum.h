
#ifndef DataFormats_L1Trigger_ETSum_h
#define DataFormats_L1Trigger_ETSum_h

namespace l1t {
  struct EtSum{

    enum EtSumType {
      kTotalEt,
      kTotalHt,
      kMissingEt,
      kMissingHt,
      kTotalEtx,
      kTotalEty,
      kTotalHtx,
      kTotalHty,
      kMissingEtHF,
      kTotalEtxHF,
      kTotalEtyHF,
      kMinBiasHFP0,
      kMinBiasHFM0,
      kMinBiasHFP1,
      kMinBiasHFM1,
      kTotalEtHF,
      kTotalEtEm,
      kTotalHtHF,
      kTotalHtxHF,
      kTotalHtyHF,
      kMissingHtHF,
      kTowerCount
    };

    EtSum(){}

    ~EtSum();

  };

}

#endif


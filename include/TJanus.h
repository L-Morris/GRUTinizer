#ifndef _TJANUS_H_
#define _TJANUS_H_

#include "TClonesArray.h"

#include "TDetector.h"
#include "TJanusHit.h"

class TJanus : public TDetector {
public:
  TJanus();
  virtual ~TJanus();

  void Copy(TObject& obj) const;

  virtual void Clear(Option_t* opt = "");

  virtual bool AddRawData(TSmartBuffer buf);
  virtual int  BuildHits();

  virtual void InsertHit(const TDetectorHit&);
  virtual TJanusHit&    GetJanusHit(int i);
  virtual TDetectorHit& GetHit(int i);
  virtual int Size();

private:
  void Build_VMUSB_Read(TSmartBuffer buf);

  TClonesArray* janus_hits; //->
  std::vector<TSmartBuffer> raw_data; //!

  ClassDef(TJanus,1);
};

#endif /* _TJANUS_H_ */
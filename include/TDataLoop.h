#ifndef _TDATALOOP_H_
#define _TDATALOOP_H_

#ifndef __CINT__
#include <atomic>
#include <condition_variable>
#include <thread>
#endif

#include <cstdlib>
#include <iostream>
#include <map>

#include <TNamed.h>

#include "StoppableThread.h"
#include "ThreadsafeQueue.h"
#include "TRawEvent.h"

class TRawEventSource;

class TDataLoop : public StoppableThread  {
public:
  static TDataLoop *Get(std::string name="", TRawEventSource* source=0);
  virtual ~TDataLoop();

  const TRawEventSource& GetSource() const { return *source; }

  std::string Status();
  virtual void ClearQueue();

  //protected:
  bool Iteration();

  int Pop(TRawEvent &event);

  size_t GetItemsPushed()  { return output_queue.ItemsPushed(); }
  size_t GetItemsPopped()  { return output_queue.ItemsPopped(); }
  size_t GetItemsCurrent() { return output_queue.Size();        }
  size_t GetRate()         { return 0; }

  void ReplaceSource(TRawEventSource* new_source);
  void ResetSource();

  void SetSelfStopping(bool self_stopping) { fSelfStopping = self_stopping; }
  bool GetSelfStopping() const { return fSelfStopping; }

private:
  TDataLoop(std::string name,TRawEventSource* source);
  //ThreadsafeQueue<TRawEvent>& output_queue,std::string name="");
  TDataLoop();
  TDataLoop(const TDataLoop& other);
  TDataLoop& operator=(const TDataLoop& other);

  ThreadsafeQueue<TRawEvent> output_queue;
  TRawEventSource* source;

  bool fSelfStopping;

#ifndef __CINT__
  std::mutex source_mutex;
#endif

  ClassDef(TDataLoop, 0);
};

#endif /* _TDATALOOP_H_ */

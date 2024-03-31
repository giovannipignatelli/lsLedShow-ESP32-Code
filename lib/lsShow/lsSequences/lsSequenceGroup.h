#include "lsSequence.h"

#define SPRINTINFOSEQUENCEGROUP Serial.print("\tSequencese: ");Serial.print(_sequences.size());Serial.print("\tCurrent sequence: ");Serial.print(_current_sequence);\
                          Serial.print("\tRepeat: ");Serial.print(_repeatCount);Serial.print("\tCurrent Run: ");Serial.print(_runs);\
                          Serial.print("\tCR: ");Serial.print(frame);Serial.print("\tRender Every: ");Serial.print(_renderEveryNFrames);Serial.print("\tNext Frame Render: ");Serial.print(_nextFrameRender);Serial.print("\tChange Color every: ");Serial.print(_changeColorEveryNFrames);\
                          Serial.println("");

class lsSequenceGroup: public lsSequence {
  
    LinkedList<lsSequence*> _sequences = LinkedList<lsSequence*>();

    uint8_t _current_sequence = 0;
  

  public:
    
    lsSequenceGroup() {
      //this->setFusion(MASK);
      _type=LS_SEQUENCES_TYPES::lsSequenceGroup;
    }

    void getFirstFrameRender(CRGB * leds)  {
      fill_solid(leds,STRIP_NUM_LEDS,SEQUENCE_SECONDARY_COLOR);
    };


    CRGB *getLeds() { return nullptr;}

    void privateRender(unsigned long frame)  { 
      if (( _sequences.size()>0 && _current_sequence < _sequences.size() ) &&  (SEQUENCE_RUN<_repeatCount )) {
        _sequences.get(this->_current_sequence)->render(frame);
        if (_sequences.get(this->_current_sequence)->isCompleted(frame)){
          _sequences.get(this->_current_sequence)->printInfo(frame);
          _sequences.get(this->_current_sequence)->postRender();
          _sequences.get(this->_current_sequence)->reset();
          _current_sequence++;
          
          if(_current_sequence == this->_sequences.size()) {
            _current_sequence=0;
            _runs++;
          }
          else{
            _sequences.get(this->_current_sequence)->startAt(frame++);
            _sequences.get(this->_current_sequence)->preRender();
          }
        }
      }
      else {        
        if (SEQUENCE_RUN == _repeatCount) this->parentLevel->sequenceCompleted(frame);
      }
    }

    lsSequence &addSequence(lsSequence *seq){
      seq->startAt((_sequences.size()==0) ? 0 : _sequences.get(this->_sequences.size()-1)->getLastFrame());
      seq->setStrip(this->_Strip);
      seq->setParentLevel(nullptr);
      _sequences.add(seq);
      return *this->_sequences.get(this->_sequences.size()-1);
    }

    lsSequence &lastSequence(){
      return *this->_sequences.get(this->_sequences.size()-1);
    }    

    lsSequence &getSequence(int num){
      return *this->_sequences.get(num);
    }   

};


#ifndef PROCESSOR_H
#define PROCESSOR_H



class Processor {
 public:

  float Utilization();  // TODO: See src/processor.cpp

  // TODO: Declare any necessary private members

 private:

//Declaring floats needed based on the stackoverflow comment
 float PrevIdle, previdle, previowait, Idle, PrevNonIdle, prevuser, prevnice, prevsystem, previrq, prevsoftirq, prevsteal, NonIdle, totald, Total, PrevTotal, idled, CPU_Percentage;
 
};

#endif
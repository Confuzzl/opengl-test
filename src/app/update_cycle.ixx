export module app.update_cycle;

export struct UpdateCycle {
  unsigned short rate;
  double length;
  double prevTime = 0, currTime = 0, dt = 0;
  unsigned long long prevCount = 0, currCount = 0;

  UpdateCycle(const unsigned short rate);

  void bottleNeck(const unsigned short bottleneck);

  bool pastLength(const double time);
  void pushNewTime(const double newCurrTime);
  void pushCount();
};
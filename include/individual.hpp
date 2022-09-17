struct Solution{
    int* chromosome;
    int size;
};

struct Individual{
  Solution solution;
  double fitness;
  int updated;
};

struct Population{
    Individual *individual;
    int size;
};

class TDMA {
  public Delays!: number[];
  public Threshold!: number;

  public constructor(tdma: Partial<TDMA>) {
    Object.assign(this, tdma);
  }

  get ChannelCount() {
    return this.Delays.length;
  }

  get HasNext() {
    return this.Delays.filter((delay) => delay > 0).length > 0;
  }

  ThresholdCheck() {
    console.log(this.Delays);
    for (const [index, delay] of this.Delays.entries()) {
      if (delay < this.Threshold && delay > 0) {
        console.log("Assign Slot ", index * 417 + 1, "to", (index + 1) * 417);
        // As we are done with one signal
        // Reduce Delay
        this.Delays[index] = 0;
      } else if (delay <= 0) {
        // We are completely done with the channel
        console.log("Idle for Channel ", index);
      } else {
        // We exceeded the threshold
        // So let's bring the delay down in this case
        this.Delays[index] -= this.Threshold;
        console.log("Idle for Channel ", index, "Delay too High");
      }
    }
    // Remove Channel Delays Not under Consideration at the moment
  }
}

const tdma = new TDMA({
  Delays: [12, 14, 12, 11],
  Threshold: 10,
});

for (let cycle = 0; tdma.HasNext; ++cycle) {
  console.log("Cycle", cycle);
  tdma.ThresholdCheck();
}

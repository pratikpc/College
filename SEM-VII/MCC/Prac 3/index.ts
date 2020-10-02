export default class CDMA {
  WalshCodeSize: number = 3;
  data: number[][] = [];
  codes: number[][] = [];

  public constructor(cdma: Partial<CDMA>) {
    Object.assign(this, cdma);
  }

  private WalshCache: number[][] = [];

  private static ToBipolar(data: number[] | number): number[] {
    if (Array.isArray(data)) return data.map((val) => (val > 0 ? 1 : -1));
    return [data > 0 ? 1 : -1];
  }
  private static Flip(data: (number[] | number)[]): (number | number[])[] {
    return data.map(
      (val) =>
        (Array.isArray(val) ? CDMA.Flip(val) : val >= 0 ? -1 : 1) as typeof val
    );
  }

  // It's possible One value is Less than another
  // So we extend that value
  // 1 * [3,4,5]
  // Becomes [1,1,1] * [3,4,5]
  // [1,2] * [3,4,5]
  // Becomes [1,2,1] * [3,4,5]
  private static Repeat<T>(left: T[], right: T[]): [T[], T[]] {
    if (right.length < left.length) return CDMA.Repeat(right, left);
    if (right.length == left.length) return [left, right];
    let dataIn: typeof left = [...left];
    for (let i = left.length; i < right.length; ++i) {
      const datum = left[i % left.length];
      dataIn.push(datum);
    }
    return [dataIn, right];
  }

  public set Data(data: number[]) {
    this.data = data.map((datum) => CDMA.ToBipolar(datum));
  }

  private static SpreadCodeSingle(
    dataIn_: number[],
    code_: number[]
  ): number[] {
    const [dataIn, code] = CDMA.Repeat(dataIn_, code_);
    return dataIn.map((datum, idx) => datum * code[idx]);
  }

  public get UserSpreadCode() {
    return CDMA.SpreadCode(this.data, this.codes);
  }
  public get SignalSent() {
    return CDMA.Superposition(this.UserSpreadCode);
  }

  public get RecoveredSignal() {
    return CDMA.SpreadCode([this.SignalSent], this.codes);
  }

  public get RecoveredData() {
    const recovered = CDMA.ToBipolar(
      CDMA.FindSignal(this.RecoveredSignal)
    ).map((val) => (val <= 0 ? 0 : 1));
    return recovered;
  }

  public set CodeWalshIndices(codes: number[]) {
    this.codes = codes.map((code) => CDMA.ToBipolar(this.WalshCode[code]));
  }

  private static SpreadCode(
    dataIn_: number[][],
    code_: number[][]
  ): number[][] {
    const [dataIn, code] = CDMA.Repeat(dataIn_, code_);
    return dataIn.map((datum, idx) => CDMA.SpreadCodeSingle(datum, code[idx]));
  }

  private static Superposition(arr: number[][]) {
    const result: number[] = [];
    // [[1,2],[3,4]] = [4,6]
    for (let i = 0; i < arr[0].length; ++i) {
      let res = 0;
      for (let j = 0; j < arr.length; ++j) res += arr[j][i];
      result.push(res);
    }
    return result;
  }

  private static FindSignal(recover: number[][]) {
    // Calculate sum
    return recover.map((rec) =>
      rec.reduce((left, right) => Number(left as number) + Number(right))
    );
  }

  private static WalshCodeGen(size_: number) {
    const size = Math.pow(2, Math.ceil(Math.log(size_) / Math.log(2)));
    if (size <= 1) return [[-1]];
    const w0 = CDMA.WalshCodeGen(size / 2);
    const w1 = w0.slice();
    const w2 = w0.slice();
    const w3 = CDMA.Flip(w0.slice()) as typeof w0;
    function CombineW0W1(left: number[][], right: number[][]) {
      const res = [];
      while (true) {
        const leftTop = left.pop();
        const rightTop = right.pop();
        if (leftTop == null || rightTop == null) break;
        res.push([...leftTop, ...rightTop]);
      }
      return res.reverse();
    }

    const w: number[][] = [...CombineW0W1(w0, w1), ...CombineW0W1(w2, w3)];
    return w;
  }

  public get WalshCode() {
    this.WalshCodeSize = Math.pow(
      2,
      Math.ceil(Math.log(this.WalshCodeSize) / Math.log(2))
    );
    if (this.WalshCodeSize === this.WalshCache.length) return this.WalshCache;
    this.WalshCache = CDMA.WalshCodeGen(this.WalshCodeSize);
    return this.WalshCache;
  }
}

import readline from "readline";

const rl = readline.createInterface({
  input: process.stdin,
  output: process.stdout,
});

const it = rl[Symbol.asyncIterator]();
const data = [];
const codeIndices = [];
let noOfUsers = 0;
for (; true; ++noOfUsers) {
  console.log(`Enter Data of User ${noOfUsers}\t:`);
  const elem = Number((await it.next()).value);
  data.push(elem);
  codeIndices.push(noOfUsers);
  console.log("Press Y to Continue\t:");
  const continueAdding = String((await it.next()).value).toLowerCase();
  if (continueAdding !== "y") break;
}
rl.close();

const cdma = new CDMA({
  WalshCodeSize: noOfUsers,
});
cdma.Data = data;
cdma.CodeWalshIndices = codeIndices;

console.log("Spread Code at Source are ", cdma.UserSpreadCode);
console.log("Signal Sent is ", cdma.SignalSent);
console.log("Signal Recovered is ", cdma.RecoveredSignal);
console.log("Data Recovered is ", cdma.RecoveredData);

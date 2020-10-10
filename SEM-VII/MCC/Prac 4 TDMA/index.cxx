#include <algorithm>
#include <vector>

#include <istream>
#include <ostream>

class TDMA
{
 private:
   using TimeT = std::size_t;
   using VecT  = std::vector<TimeT>;
   // Note that here we assume
   // Each Slot Time Index is same as User Duration Index

   VecT slotTimes{};
   VecT userTimesToTransmitLeft{};

   static constexpr TimeT threshold = 10;

 public:
   bool HasNext() const noexcept
   {
      auto const done = std::find_if(
          std::cbegin(userTimesToTransmitLeft), std::cend(userTimesToTransmitLeft),
          [](auto const timeToTransmitLeft) { return timeToTransmitLeft > 0; });
      return done != std::cend(userTimesToTransmitLeft);
   }

 public:
   void SetSlotTimesToSameAsUserCountAndFixDuration(TimeT const fixedSlotTime) noexcept
   {
      slotTimes.resize(userTimesToTransmitLeft.size());
      std::fill_n(std::begin(slotTimes), userTimesToTransmitLeft.size(), fixedSlotTime);
   }
   void AddData(typename decltype(userTimesToTransmitLeft)::size_type const index,
                TimeT const value) noexcept
   {
      userTimesToTransmitLeft[index] = value;
   }

   void ReadVals(std::ostream &ostream, std::istream &istream)
   {
      userTimesToTransmitLeft = {};
      ostream << "\nEnter Transmission Time for User (Zero to Exit)\t:";
      for (TimeT read; (istream) >> read;)
      {
         if (read == 0)
            break;
         userTimesToTransmitLeft.push_back(read);
         ostream << "\nEnter Transmission Time for User (Zero to Exit)\t:";
      }
   }

   void ThresholdCheck(std::ostream &stream)
   {
      // Find Length of Loop
      // Based on Max Param by which to execute
      auto const loopLength = userTimesToTransmitLeft.size();

      TimeT       currentTransmittingTime = 0;
      std::size_t unusedSlotCount         = 0;

      for (std::size_t i = 0; i < loopLength; ++i)
      {
         auto &userTimeToTransmitLeft =
             userTimesToTransmitLeft[i % userTimesToTransmitLeft.size()];
         auto const slot = slotTimes[(i - unusedSlotCount) % slotTimes.size()];

         if (userTimeToTransmitLeft >= threshold)
         {
            stream << "Channel " << (i + 1) << " has not been assigned to any slot\n";
            userTimeToTransmitLeft = userTimeToTransmitLeft - threshold;
            unusedSlotCount += 1;
         }
         else if (userTimeToTransmitLeft < threshold && userTimeToTransmitLeft > 0)
         {
            stream << "Channel " << (i + 1) << " has been assigned to "
                   << "slot " << currentTransmittingTime << " to "
                   << (currentTransmittingTime + slot) << '\n';
            userTimeToTransmitLeft = 0;
         }
         else
         {
            // Ignore
            stream << "Time Slot " << currentTransmittingTime << " to "
                   << (currentTransmittingTime + slot) << " idle" << '\n';
         }
         currentTransmittingTime += (slot + 1);
      }
   }
};

#include <iostream>

int main()
{
   TDMA tdma{};
   tdma.ReadVals(std::cout, std::cin);
   tdma.SetSlotTimesToSameAsUserCountAndFixDuration(417);
   for (std::size_t i = 1; tdma.HasNext(); ++i)
   {
      std::cout << "Cycle " << i << "\n";
      tdma.ThresholdCheck(std::cout);
   }
}

/*
Enter Transmission Time for User (Zero to Exit) :11
Enter Transmission Time for User (Zero to Exit) :12
Enter Transmission Time for User (Zero to Exit) :10
Enter Transmission Time for User (Zero to Exit) :9
Enter Transmission Time for User (Zero to Exit) :8
Enter Transmission Time for User (Zero to Exit) :12
Enter Transmission Time for User (Zero to Exit) :7
Enter Transmission Time for User (Zero to Exit) :0
Cycle 1
Channel 1 has not been assigned to any slot
Channel 2 has not been assigned to any slot
Channel 3 has not been assigned to any slot
Channel 4 has been assigned to slot 1254 to 1671
Channel 5 has been assigned to slot 1672 to 2089
Channel 6 has not been assigned to any slot
Channel 7 has been assigned to slot 2508 to 2925
Cycle 2
Channel 1 has been assigned to slot 0 to 417
Channel 2 has been assigned to slot 418 to 835
Time Slot 836 to 1253 idle
Time Slot 1254 to 1671 idle
Time Slot 1672 to 2089 idle
Channel 6 has been assigned to slot 2090 to 2507
Time Slot 2508 to 2925 idle
*/

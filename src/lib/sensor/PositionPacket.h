/******************************************************************************
 * Copyright (C) 2011 by Jerome Maye                                          *
 * jerome.maye@gmail.com                                                      *
 *                                                                            *
 * This program is free software; you can redistribute it and/or modify       *
 * it under the terms of the Lesser GNU General Public License as published by*
 * the Free Software Foundation; either version 3 of the License, or          *
 * (at your option) any later version.                                        *
 *                                                                            *
 * This program is distributed in the hope that it will be useful,            *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of             *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the              *
 * Lesser GNU General Public License for more details.                        *
 *                                                                            *
 * You should have received a copy of the Lesser GNU General Public License   *
 * along with this program. If not, see <http://www.gnu.org/licenses/>.       *
 ******************************************************************************/

/** \file PositionPacket.h
    \brief This file defines the PositionPacket class, which represents a
           Velodyne position packet
  */

#ifndef POSITIONPACKET_H
#define POSITIONPACKET_H

#include <cstdint>

#include "base/Serializable.h"

class UDPConnectionServer;
class BinaryReader;
class BinaryWriter;

/** The class PositionPacket represents a Velodyne position packet.
    \brief Velodyne position packet
  */
class PositionPacket :
  public Serializable {
public:
  /** \name Constants
    @{
    */
  /// Packet size
  static const size_t mPacketSize = 512;
  /// Gyro scale factor
  static const float mGyroScaleFactor;
  /// Temp scale factor
  static const float mTempScaleFactor;
  /// Temp offset
  static const float mTempOffset;
  /// Accel scale factor
  static const float mAccelScaleFactor;
  /** @}
    */

  /** \name Constructors/Destructor
    @{
    */
  /// Default constructor
  PositionPacket() :
     mTimestamp(0) {}
  /// Copy constructor
  PositionPacket(const PositionPacket& other) :
      Serializable(),
      mTimestamp(other.mTimestamp) {}
  /// Assignment operator
  PositionPacket& operator = (const PositionPacket& other);
  /// Destructor
  ~PositionPacket() {}
  /** @}
    */

  /** \name Accessors
    @{
    */
  /// Returns the timestamp of the acquisition [ns]
  int64_t getTimestamp() const {
    return mTimestamp;
  }
  /// Sets the timestamp
  void setTimestamp(int64_t timestamp) {
    mTimestamp = timestamp;
  }
  /// Returns the gyro1
  float getGyro1() const;
  /// Returns the gyro2
  float getGyro2() const;
  /// Returns the gyro3
  float getGyro3() const;
  /// Returns the temp1
  float getTemp1() const;
  /// Returns the temp2
  float getTemp2() const;
  /// Returns the temp3
  float getTemp3() const;
  /// Returns the accel1 x
  float getAccel1X() const;
  /// Returns the accel2 x
  float getAccel2X() const;
  /// Returns the accel3 x
  float getAccel3X() const;
  /// Returns the accel1 y
  float getAccel1Y() const;
  /// Returns the accel2 y
  float getAccel2Y() const;
  /// Returns the accel3 y
  float getAccel3Y() const;
  /// Returns the GPS timestamp [us]
  uint32_t getGPSTimestamp() const {
    return mGPSTimestamp;
  }
  /// Returns the NMEA sentence
  const uint8_t* getNMEASentence() const {
    return mNMEASentence;
  }
  /** @}
    */

  /** \name Methods
    @{
    */
  /// Binary read from UDP
  void readBinary(UDPConnectionServer& stream);
  /// Binary write into a output stream
  void writeBinary(std::ostream& stream) const;
  /// Binary read from an input stream
  void readBinary(std::istream& stream);
  /** @}
    */

protected:
  /** \name Stream methods
    @{
    */
  /// Reads from standard input
  virtual void read(std::istream& stream);
  /// Writes to standard output
  virtual void write(std::ostream& stream) const;
  /// Reads from a file
  virtual void read(std::ifstream& stream);
  /// Writes to a file
  virtual void write(std::ofstream& stream) const;
  /** @}
    */

  /** \name Protected methods
    @{
    */
  /// Read raw packet
  void readRawPacket(BinaryReader& stream);
  /// Write raw packet
  void writeRawPacket(BinaryWriter& stream) const;
  /** @}
    */

  /** \name Protected members
    @{
    */
  /// Timestamp of the packet in nanoseconds since the epoch
  int64_t mTimestamp;
  /// Unused bytes
  uint8_t mNotUsed1[14];
  /// Gyro 1
  uint16_t mGyro1;
  /// Temp 1
  uint16_t mTemp1;
  /// Accel 1 x
  uint16_t mAccel1X;
  /// Accel 1 y
  uint16_t mAccel1Y;
  /// Gyro 2
  uint16_t mGyro2;
  /// Temp 2
  uint16_t mTemp2;
  /// Accel 2 x
  uint16_t mAccel2X;
  /// Accel 2 y
  uint16_t mAccel2Y;
  /// Gyro 3
  uint16_t mGyro3;
  /// Temp 3
  uint16_t mTemp3;
  /// Accel 3 x
  uint16_t mAccel3X;
  /// Accel 3 y
  uint16_t mAccel3Y;
  /// Unused bytes
  uint8_t mNotUsed2[160];
  /// GPS timestamp
  uint32_t mGPSTimestamp;
  /// Unused bytes
  uint8_t mNotUsed3[4];
  /// NMEA sentence
  uint8_t mNMEASentence[72];
  /// Unused bytes
  uint8_t mNotUsed4[220];
  /// Raw data
  uint8_t mRawPacket[mPacketSize];
  /** @}
    */

};

#endif // POSITIONPACKET_H

/*
    Copyright (c) 2007-2015 Contributors as noted in the AUTHORS file

    This file is part of 0MQ.

    0MQ is free software; you can redistribute it and/or modify it under
    the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation; either version 3 of the License, or
    (at your option) any later version.

    0MQ is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <assert.h>

#include <zmq.h>
#include <zmq_utils.h>

#include "jzmq.hpp"
#include "util.hpp"
#include "org_zeromq_Utils.h"

/*
 * Class:     org_zeromq_Utils
 * Method:    z85_decode
 * Signature: (Ljava/lang/String;)[B
 */
JNIEXPORT jbyteArray JNICALL
Java_org_zeromq_Utils_z85_1decode(JNIEnv* env, jclass, jstring encoded) {
  const char* data = env->GetStringUTFChars(encoded, JNI_FALSE);
  size_t len = env->GetStringLength(encoded) * 4 / 5;
  char decoded[len];
  uint8_t* r = zmq_z85_decode(reinterpret_cast<uint8_t*>(decoded), (char*)data);
  if (!r) {
    jclass Exception = env->FindClass("java/lang/IllegalArgumentException");
    env->ThrowNew(Exception, "Couldn't z85 decode the value.");
  }
  jbyteArray result = env->NewByteArray(len);
  env->SetByteArrayRegion(result, 0, len, (const jbyte*)decoded);
  env->ReleaseStringUTFChars(encoded, data);
  return result;
}

/*
 * Class:     org_zeromq_Utils
 * Method:    z85_encode
 * Signature: ([B)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL
Java_org_zeromq_Utils_z85_1encode(JNIEnv* env, jclass, jbyteArray raw) {
  size_t len = env->GetArrayLength(raw);

  char dest[len * 5 / 4 + 1];
  jbyte* bytes = env->GetByteArrayElements(raw, NULL);
  char* r = zmq_z85_encode(dest, reinterpret_cast<uint8_t*>(bytes), len);
  env->ReleaseByteArrayElements(raw, bytes, 0);

  if (!r) {
    jclass Exception = env->FindClass("java/lang/IllegalArgumentException");
    env->ThrowNew(Exception, "Couldn't z85 encode the value.");
  }
  return env->NewStringUTF(dest);
}

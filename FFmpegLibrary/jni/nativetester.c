/*
 * nativetester.c
 * Copyright (c) 2012 Jacek Marchwicki
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#include <jni.h>
#include <android/log.h>
#include <cpu-features.h>

#include <stdlib.h>

#include "helpers.h"
#include "nativetester.h"

#define LOG_TAG "AVEngine:nativetester.c"
#define LOG_LEVEL 10

jboolean jni_nativetester_is_neon(JNIEnv *env, jobject thiz) {
#ifdef FEATURE_NEON
	uint64_t features;
	if (android_getCpuFamily() != ANDROID_CPU_FAMILY_ARM) {
		LOGI(5, "Not an ARM CPU\n");
		return JNI_FALSE;
	}

	features = android_getCpuFeatures();

	if ((features & ANDROID_CPU_ARM_FEATURE_ARMv7) == 0) {
		LOGI(5, "Not an ARMv7 CPU\n");
		return JNI_FALSE;
	}

	if ((features & ANDROID_CPU_ARM_FEATURE_NEON) == 0) {
		LOGI(5, "CPU doesn't support NEON\n");
		return JNI_FALSE;
	}

	return JNI_TRUE;
#else
	return JNI_FALSE;
#endif
}


/*
 * Project: mxr.core-lib
 *
 * Copyright (c) 2020,  Prof. Dr. Nikolaus Wulff
 * University of Applied Sciences, Muenster, Germany
 * Lab for computer sciences (Lab4Inf).
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

package de.lab4inf.mxr.core;

import static java.lang.annotation.ElementType.*;
import static java.lang.annotation.RetentionPolicy.CLASS;

import java.lang.annotation.*;

/**
 * Marker annotation for a package wide none null annotation.
 * 
 * @author nwulff
 * @since 10.10.2021
 */
@Documented
@Retention(CLASS)
@Target({ TYPE, FIELD, METHOD, PACKAGE, PARAMETER, LOCAL_VARIABLE, TYPE_PARAMETER })
public @interface NonNullByDefault {

}

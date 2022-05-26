/**
 * 
 */
package de.lab4inf.mxr.engine;

import java.util.Objects;

import de.lab4inf.mxr.core.Fact;
import de.lab4inf.mxr.core.NonNull;

/**
 * @author lukas
 *
 */
class Key<Problem, facts extends Fact> {
	private Problem p;
	private Class<?> f;
	private Class<?> sig[];
 
	
	public Key(Problem p, facts f) {
		this.p = Objects.requireNonNull(p);
		this.f = f.getClass();
		this.sig = f.signature();
	}
	@Override
	public int hashCode() {
		int sigHash = 0;
		for(Class<?> clazz: this.sig) {
			sigHash += clazz.hashCode();
		}
		return this.p.hashCode()^this.f.hashCode()^sigHash;
		}
	@Override
	public boolean equals(Object o) {
		if (null == o)
			return false;
		if (this == o)
			return true;
		if (o.getClass() == this.getClass()) {
			@NonNull
			Key<?, ?> that = Key.class.cast(o);
			return this.p.equals(that.p) 
					&& this.f.equals(that.f)
					&& this.sigEquals(that.sig);
		}
		return false;
	}
	protected boolean sigEquals(Class<?> signature[]) {
		if(signature.length == this.sig.length) {
			int i = 0;
			boolean rv= true;
			for(Class<?> clazz: this.sig) {
				rv = rv && clazz.equals(signature[i++]);
			}
			return rv;
		}
		return false;
	}
}

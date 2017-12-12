import testProgram from './test-program'
import test from 'ava'

test('should compile a simple program', testProgram({ program: 'hello' }))

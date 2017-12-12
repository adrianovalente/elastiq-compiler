import testProgram from './test-program'
import test from 'ava'

test('simple hello world program', testProgram({ program: 'hello' }))
test('arithmetic expressions', testProgram({ program: 'arithmetic-expression' }))
test('logical asserts', testProgram({ program: 'logical-assert' }))

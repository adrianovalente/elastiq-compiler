import testProgram from './test-program'
import test from 'ava'

console.log('\x1b[34mINTEGRATION TESTS\x1b[0m')
test('simple hello world program', testProgram({ program: 'hello' }))
test('arithmetic expressions', testProgram({ program: 'arithmetic-expression' }))
test('logical asserts', testProgram({ program: 'logical-assert' }))
test('factorial', testProgram({ program: 'factorial' }))

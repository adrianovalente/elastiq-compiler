import testProgram from './test-program'
import test from 'ava'

test('should compile a simple program', async t => {
  const program = await testProgram({ program: 'hello' })

  t.pass()
})

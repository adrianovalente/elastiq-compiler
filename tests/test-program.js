import { readFileSync } from 'fs'
import { exec } from 'child_process'
export default function testProgram ({ program, shouldFail = false }) {

  return async function (t) {
    await execCommand(`dist/elastiq-compiler tests/fixtures/${program}.el /tmp/${program}.asm`)
      .then(r => {
        if (shouldFail !== r.failed) {
          console.error(r.output)

          throw new Error(`Compilation should ${ !shouldFail ? 'not ' : ''}fail`)
        }

        if (!shouldFail) {
          const expected = readFileSync(`tests/fixtures/${program}.fixture.asm`, 'utf-8').trim()
          const code = readFileSync(`/tmp/${program}.asm`, 'utf-8').trim()

          if (code !== expected) console.error(r.output)
          t.is(code, expected)
        }

        return r
      })

    t.pass()
  }

}

const execCommand = command => {
  // console.log(`Running command: ${command}`)

  return new Promise((resolve, reject) => {
    exec(command, (err, stdout, stderr) => {
      resolve({
        output: stdout,
        failed: !!err
      })
    })
  })
}

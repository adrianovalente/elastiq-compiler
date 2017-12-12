import { readFileSync } from 'fs'
import { exec } from 'child_process'
export default function testProgram ({ program, shouldFail = false }) {

  return async function (t) {
    await Promise.all([
      execCommand(`dist/elastiq-compiler tests/fixtures/${program}.el`),
      Promise.resolve(readFileSync(`tests/fixtures/${program}.fixture.asm`, 'utf-8').trim())
    ])
      .then(function ([r, expected]) {
        if (shouldFail !== r.failed) {
          console.error(r.output)

          throw new Error(`Compilation should ${ !shouldFail ? 'not ' : ''}fail`)
        }

        if (!shouldFail) {
          const program = r.output.split('Program is valid!')[1].trim()
          if (program !== expected) console.error(r.output)
          t.is(program, expected)
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
